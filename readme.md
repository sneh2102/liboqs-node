## Requirements

- Linux 
- [NVM](https://4geeks.com/how-to/install-nvm-linux)

## Quickstart

### Linux and Mac

1. Install dependencies:

	On Ubuntu:
		
		 sudo apt install astyle cmake gcc ninja-build libssl-dev python3-pytest python3-pytest-xdist unzip xsltproc doxygen graphviz python3-yaml valgrind libcurl4-openssl-dev libjson-c-dev

2. Run run.sh file

	```
	chmod +x run.sh
	./run.sh
	```
3. Change node version

	```bash
	nvm install 18
	nvm use 18
	```

4. Run 

	```bash
	node Kems.js
	```

4. Check the output
  

	```bash
		[
		'BIKE-L1',
		'BIKE-L3',
		'Classic-McEliece-348864',
		'Classic-McEliece-348864f',
		'Classic-McEliece-460896',
		'Classic-McEliece-460896f',
		'Classic-McEliece-6688128',
		'Classic-McEliece-6688128f',
		'Classic-McEliece-6960119',
		'Classic-McEliece-6960119f',
		'Classic-McEliece-8192128',
		'Classic-McEliece-8192128f',
		'HQC-128',
		'HQC-192',
		'HQC-256',
		'Kyber512',
		'Kyber768',
		'Kyber1024',
		'Kyber512-90s',
		'Kyber768-90s',
		'Kyber1024-90s',
		'NTRU-HPS-2048-509',
		'NTRU-HPS-2048-677',
		'NTRU-HPS-4096-821',
		'NTRU-HPS-4096-1229',
		'NTRU-HRSS-701',
		'NTRU-HRSS-1373',
		'ntrulpr653',
		'ntrulpr761',
		'ntrulpr857',
		'ntrulpr1277',
		'sntrup653',
		'sntrup761',
		'sntrup857',
		'sntrup1277',
		'LightSaber-KEM',
		'Saber-KEM',
		'FireSaber-KEM',
		'FrodoKEM-640-AES',
		'FrodoKEM-640-SHAKE',
		'FrodoKEM-976-AES',
		'FrodoKEM-976-SHAKE',
		'FrodoKEM-1344-AES',
		'FrodoKEM-1344-SHAKE',
		'SIDH-p434',
		'SIDH-p503',
		'SIDH-p610',
		'SIDH-p751',
		'SIDH-p434-compressed',
		'SIDH-p503-compressed',
		'SIDH-p610-compressed',
		'SIDH-p751-compressed',
		'SIKE-p434',
		'SIKE-p503',
		'SIKE-p610',
		'SIKE-p751',
		'SIKE-p434-compressed',
		'SIKE-p503-compressed',
		'SIKE-p610-compressed',
		'SIKE-p751-compressed'
		]
		Public Key:  <Buffer ef a8 ca 7a 18 16 c0 69 9e c6 06 39 28 a3 b0 59 95 88 63 35 0b f3 75 2f ca cc 15 65 48 7f c2 57 c3 19 96 44 6a 79 58 04 e6 89 f8 e2 60 81 49 a2 71 25 ... 750 more bytes>
		Secret Key:  <Buffer 59 a5 77 76 a5 a5 7e 97 3d 31 d9 0e b6 92 29 51 e8 0c 67 b5 2d 84 cc 01 b8 03 c2 8d 5c 08 48 30 20 59 92 a8 34 a1 7b 01 63 4c 36 60 3f db d3 4d 11 bc ... 1582 more bytes>
		Server Public Key:  <Buffer 71 d5 86 ac 8a 1f 28 f6 a5 37 6b 73 a7 e7 98 26 09 8a ff b8 ae 56 b6 9d de 57 c0 4f 14 b7 f0 3a 26 4f c9 ce ef f1 77 89 81 68 5d 07 7d f0 37 a5 42 87 ... 750 more bytes>
		Client Encapsulation:  {
		ciphertext: <Buffer d4 95 1c 34 d3 07 50 ee 37 07 c2 70 ab ee ed 9c bf af 84 44 8a 0c 89 f8 df 47 44 86 20 23 9b ed 5a 61 51 e0 25 d1 b0 5a 51 11 60 07 a7 44 b1 cc 68 27 ... 718 more bytes>,
		sharedSecret: <Buffer f9 24 7e c7 30 31 4d 34 fe d0 3b 99 50 d0 5d bc 62 f5 b3 fe 38 95 fc ce 2d 3b 87 f2 c6 e0 fe 9d>
		}
		Shared Secret:  <Buffer f9 24 7e c7 30 31 4d 34 fe d0 3b 99 50 d0 5d bc 62 f5 b3 fe 38 95 fc ce 2d 3b 87 f2 c6 e0 fe 9d>
		Server Decapsulation:  <Buffer f9 24 7e c7 30 31 4d 34 fe d0 3b 99 50 d0 5d bc 62 f5 b3 fe 38 95 fc ce 2d 3b 87 f2 c6 e0 fe 9d>
		Shared Secret:  true
		```
