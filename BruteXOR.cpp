#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

string numerals = "0123456789";
string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// The XOR encryption function that will be used
string XOR(string data, const char* key){
	// store the xored string of chars
	string xorstr = data;
	// loop that will encrypt each byte of data passed in with the given key
	for(int i = 0; i < xorstr.length(); i++){
		// xor each byte of the string by the current byte of the key
		xorstr[i] = data[i] ^ key[i];
	}
	return xorstr;
}

void bruteForce(int keylen, string ciphertext,
	string plaintext, bool enableAlphabetLower,
	bool enableAlphabetUpper, bool enableNumerals,
	const char* tempkey = "")
	{
	// counts key generations
	static int iterations = 0;
	
	string consoleTitle;
	// store the data decrypted with the generated key
	string decipher;
	iterations++;
	if(keylen == 0){
		decipher = XOR(ciphertext, tempkey);
		consoleTitle = "Key: " + string(tempkey);
		cout << decipher << " Iterations: " << iterations << endl;
		SetConsoleTitle(consoleTitle.c_str());
		
		// check if the generated decrypted data matches the plaintext
		// if it does, the right key to crypt the cipher was found
		if(decipher == plaintext){
			cout << "Key found. It is '" << tempkey << "'";
			cout << "It took " << iterations << " iterations to find the key";
			getchar();
		}
		return;
	}
	// for the lower alphabet
	if(enableAlphabetLower){
		for(int i = 0; i < 26; i++){
			string appended = tempkey + alphabetLower[i];
			bruteForce(keylen - 1, ciphertext, plaintext,
			enableAlphabetLower, enableAlphabetUpper, enableNumerals, appended.c_str());
		}
	}
	
	// for the upper alphabet
	if(enableAlphabetUpper){
		for(int i = 0; i < 26; i++){
			string appended = tempkey + alphabetUpper[i];
			bruteForce(keylen - 1, ciphertext, plaintext,
			enableAlphabetLower, enableAlphabetUpper, enableNumerals, appended.c_str());
		}
	}
	
	// for numerals
	if(enableNumerals){
		for(int i = 0; i < 10; i++){
			string appended = tempkey + numerals[i];
			bruteForce(keylen - 1, ciphertext, plaintext,
			enableAlphabetLower, enableAlphabetUpper, enableNumerals, appended.c_str());
		}
	}

}	


// driver
int main(){
	// stores the given plain/cipher text
	string ciphertext, plaintext;
	// store the given inputs
	cout << "Enter a ciphertext in ascii: ";
	cin >> ciphertext;
	cout << "Enter a plaintext associated with the given cipher: ";
	cin >> plaintext;
	bruteForce(plaintext.length(), ciphertext, plaintext, true, true, true);
} 