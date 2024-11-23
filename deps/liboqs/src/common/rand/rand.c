// SPDX-License-Identifier: MIT

#include <stdio.h>
#if defined(_WIN32)
#include <windows.h>
#include <wincrypt.h>
#define strcasecmp _stricmp
#else
#include <unistd.h>
#include <strings.h>
#if defined(__APPLE__)
#include <sys/random.h>
#else
#include <unistd.h>
#endif
#endif
#include <fcntl.h>
#include <stdlib.h>

#include <curl/curl.h>
#include <oqs/oqs.h>
#include <json-c/json.h> 
#include <string.h>

void OQS_randombytes_system(uint8_t *random_array, size_t bytes_to_read);
void OQS_randombytes_nist_kat(uint8_t *random_array, size_t bytes_to_read);
#ifdef OQS_USE_OPENSSL
void OQS_randombytes_openssl(uint8_t *random_array, size_t bytes_to_read);
#endif

#ifdef OQS_USE_OPENSSL
#include <openssl/rand.h>
// Use OpenSSL's RAND_bytes as the default PRNG
static void (*oqs_randombytes_algorithm)(uint8_t *, size_t) = &OQS_randombytes_openssl;
#else
static void (*oqs_randombytes_algorithm)(uint8_t *, size_t) = &OQS_randombytes_system;
#endif
OQS_API OQS_STATUS OQS_randombytes_switch_algorithm(const char *algorithm) {
	if (0 == strcasecmp(OQS_RAND_alg_system, algorithm)) {
		oqs_randombytes_algorithm = &OQS_randombytes_system;
		return OQS_SUCCESS;
	} else if (0 == strcasecmp(OQS_RAND_alg_nist_kat, algorithm)) {
		oqs_randombytes_algorithm = &OQS_randombytes_nist_kat;
		return OQS_SUCCESS;
	} else if (0 == strcasecmp(OQS_RAND_alg_openssl, algorithm)) {
#ifdef OQS_USE_OPENSSL
		oqs_randombytes_algorithm = &OQS_randombytes_openssl;
		return OQS_SUCCESS;
#else
		return OQS_ERROR;
#endif
	} else {
		return OQS_ERROR;
	}
}

OQS_API void OQS_randombytes_custom_algorithm(void (*algorithm_ptr)(uint8_t *, size_t)) {
	oqs_randombytes_algorithm = algorithm_ptr;
}

OQS_API void OQS_randombytes(uint8_t *random_array, size_t bytes_to_read) {

	oqs_randombytes_algorithm(random_array, bytes_to_read);
}

#if !defined(_WIN32)
#if defined(OQS_HAVE_GETENTROPY)
void OQS_randombytes_system(uint8_t *random_array, size_t bytes_to_read) {
	while (bytes_to_read > 256) {
		if (getentropy(random_array, 256)) {
			exit(EXIT_FAILURE);
		}
		random_array += 256;
		bytes_to_read -= 256;
	}
	if (getentropy(random_array, bytes_to_read)) {
		exit(EXIT_FAILURE);
	}
}
#else
void OQS_randombytes_system(uint8_t *random_array, size_t bytes_to_read) {

	FILE *handle;
	size_t bytes_read;

	handle = fopen("/dev/urandom", "rb");
	if (!handle) {
		perror("OQS_randombytes");
		exit(EXIT_FAILURE);
	}

	bytes_read = fread(random_array, 1, bytes_to_read, handle);
	if (bytes_read < bytes_to_read || ferror(handle)) {
		perror("OQS_randombytes");
		exit(EXIT_FAILURE);
	}

	fclose(handle);
}
#endif
#else
void OQS_randombytes_system(uint8_t *random_array, size_t bytes_to_read) {
	HCRYPTPROV hCryptProv;
	if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) ||
	        !CryptGenRandom(hCryptProv, (DWORD) bytes_to_read, random_array)) {
		exit(EXIT_FAILURE); // better to fail than to return bad random data
	}
	CryptReleaseContext(hCryptProv, 0);
}
#endif

#ifdef OQS_USE_OPENSSL
#define OQS_RAND_POLL_RETRY 3
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    size_t real_size = size * nmemb;
    strncat(data, (char *)ptr, real_size);
    return real_size;
}

// Function to parse and assign the random hex string to the array
void assign_random_bytes(const char *response, uint8_t *random_array, size_t array_size) {
    size_t response_length = strlen(response);
    size_t index = 0;

    for (size_t i = 0; i < array_size; i++) {
        if (index >= response_length) {
            fprintf(stderr, "Error: Response does not contain enough data.\n");
            break;
        }
        sscanf(&response[index], "%2hhx", &random_array[i]);
        index += 2; // Move to the next hex byte
    }
}

void OQS_randombytes_openssl(uint8_t *random_array, size_t bytes_to_read) {
    const size_t max_response_length = 2048; // Max characters in a single API response
    const size_t bytes_per_call = max_response_length / 2; // Each hex byte is represented by 2 characters
    char response[4096] = ""; // Buffer for API response
    CURL *curl;
    CURLcode res;
    char url[512];
    size_t bytes_fetched = 0;

    curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "Error: CURL initialization failed.\n");
        return;
    }
        
    while (bytes_fetched < bytes_to_read) {
        snprintf(url, sizeof(url), "https://qrng.anu.edu.au/wp-content/plugins/colours-plugin/get_block_hex.php?_=%ld", time(NULL));

        // Initialize response buffer
        memset(response, 0, sizeof(response));

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            break;
        }

        size_t bytes_to_copy = bytes_per_call;
        if (bytes_fetched + bytes_to_copy > bytes_to_read) {
            bytes_to_copy = bytes_to_read - bytes_fetched;
        }

        assign_random_bytes(response, &random_array[bytes_fetched], bytes_to_copy);
        bytes_fetched += bytes_to_copy;
    }
    curl_easy_cleanup(curl);
}
#endif