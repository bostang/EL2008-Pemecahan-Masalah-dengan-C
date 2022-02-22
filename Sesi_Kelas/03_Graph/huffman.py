# Program huffman
    # melakukan dekripsi dari biner ke alfabet kemudian enkripsi dengan Huffman
    # catatan : saya melakukan ini dengan python karena python menyediakan split() method
# KAMUS
    # Variabel
        # binary_alphabet : dictionary
        # encrypted : string
        # encrypted_array : array of string
        # decrypted_array : array of character
        # length_encrypted : integer
        # my_huffman : dictionary
        # huffman_encoded : string { decrypted_array yang sudah dinyatakan dalam Huffman code kita }
    # Fungsi/Prosedur
        # function char_frequency(string) -> dictionary
            # membuat dictionary kemunculan karakter dari string yang diberikan
# ALGORITMA UTAMA

# referensi fungsi : https://stackoverflow.com/questions/40985203/counting-letter-frequency-in-a-string-python

def char_frequency(str1):
    # KAMUS LOKAL
        # Variabel
            # dict : dictionary
    # ALGORITMA
    dict = {}
    for n in str1:
        keys = dict.keys()
        if n in keys:
            dict[n] += 1
        else:
            dict[n] = 1

    return dict

binary_alphabet = {
    "00000" : 'a',
    "00001" : 'b',
    "00010" : 'c',
    "00011" : 'd',
    "00100" : 'e',
    "00101" : 'f',
    "00110" : 'g',
    "00111" : 'h',
    "01000" : 'i',
    "01001" : 'j',
    "01010" : 'k',
    "01011" : 'l',
    "01100" : 'm',
    "01101" : 'n',
    "01110" : 'o',
    "01111" : 'p',
    "10000" : 'q',
    "10001" : 'r',
    "10010" : 's',
    "10011" : 't',
    "10100" : 'u',
    "10101" : 'v',
    "10110" : 'w',
    "10111" : 'x',
    "11000" : 'y',
    "11001" : 'z'
}

encrypted = "10010 00100 01100 10100 00000 01111 00000 10010 10010 10110 01110 10001 00011 01011 10100 01010 01100 00000 01101 10011 00100 10001 00011 01000 10001 01000 00011 00000 10001 01000 10011 00100 01100 01111 00000 10011 00011 00000 01101 10011 00000 01101 00110 00110 00000 01011 01011 00000 00111 01000 10001 01101 11000 00000"
encrypted_array = encrypted.split(" ")
length_encrypted = len(encrypted_array)
decrypted_array = []

for k in range(length_encrypted):
    decrypted_array += binary_alphabet[encrypted_array[k]]

for k in range(length_encrypted):
    print(decrypted_array[k],end ="")

print()
for key in char_frequency(decrypted_array):
    print(key," -> ",char_frequency(decrypted_array)[key])

   # mencetak pesan awal dalam huffman code 

my_huffman = {
    's' : "0100",
    'e' : "001",
    'm' : "0110",
    'u' : "10100",
    'a' : "00",
    'p' : "10110",
    'w' : "100000",
    'o' : "100001",
    'r' : "1110",
    'd' : "1001",
    'l' : "0111",
    'k' : "100010",
    'n' : "1100",
    't' : "1101",
    'i' : "1111",
    'g' : "10111",
    'h' : "100011",
    'y' : "10101"
}

huffman_encoded = ""

for character in decrypted_array:
    huffman_encoded += my_huffman[character]
    huffman_encoded += " " # untuk memudahkan pembacaan oleh kita

for character in huffman_encoded:
    print(character,end="")