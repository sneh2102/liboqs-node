const oqs = require('./build/Release/oqs_node');

// Get Enabled Key Encapsulation Mechanisms
const KEMs = oqs.KEMs.getEnabledAlgorithms();
console.log(KEMs);

// Client Object of Key Encapsulation Mechanism for Kyber512
const clientKEMs = new oqs.KeyEncapsulation('Kyber512'); 

// Generate Key Pair for Client
const clientKeyPair = clientKEMs.generateKeypair();
console.log("Public Key: ",clientKeyPair);

// Export Secret Key for Client
const clientSecretKey = clientKEMs.exportSecretKey();
console.log("Secret Key: ",clientSecretKey);


// Server Object of Key Encapsulation Mechanism for Kyber512
const serverKEMs = new oqs.KeyEncapsulation('Kyber512');
const serverKeyPair = serverKEMs.generateKeypair();
console.log("Server Public Key: ",serverKeyPair);

// Encapsulate Secret for Client useing Server Public Key and returns ciphertext and shared secret
const clientEncapsulation = clientKEMs.encapsulateSecret(serverKeyPair);
console.log("Client Encapsulation: ",clientEncapsulation);

// Shared Secret for Client and Server
console.log("Shared Secret: ",clientEncapsulation.sharedSecret);

// Decapsulate Secret for Server using Srever Private Ke and returns shared secret
const serverDecapsulation = serverKEMs.decapsulateSecret(clientEncapsulation.ciphertext);
console.log("Server Decapsulation: ",serverDecapsulation);


console.log("Shared Secret: ",clientEncapsulation.sharedSecret.toString('hex') == serverDecapsulation.toString('hex'));

