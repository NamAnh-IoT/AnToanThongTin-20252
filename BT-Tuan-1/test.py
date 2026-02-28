import re

def create_matrix(key):
    # Standard Playfair uses 'I' and 'J' as the same letter
    key = key.upper().replace('J', 'I')
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ" # J is omitted
    
    # Remove duplicates from key and keep order
    seen = set()
    matrix_chars = []
    for char in (key + alphabet):
        if char.isalpha() and char not in seen:
            seen.add(char)
            matrix_chars.append(char)
            
    # Create 5x5 grid
    return [matrix_chars[i:i+5] for i in range(0, 25, 5)]

def find_position(matrix, char):
    for r, row in enumerate(matrix):
        if char in row:
            return r, row.index(char)
    return None

def prepare_text(text):
    # Clean text: uppercase and remove non-alphas
    text = re.sub(r'[^A-Z]', '', text.upper().replace('J', 'I'))
    
    prepared = []
    i = 0
    while i < len(text):
        char1 = text[i]
        # Rule 1: If same letters, insert 'X'
        if i + 1 < len(text):
            char2 = text[i+1]
            if char1 == char2:
                prepared.append(char1 + 'X')
                i += 1
            else:
                prepared.append(char1 + char2)
                i += 2
        else:
            # Rule 2: If odd length, add 'X' at the end
            prepared.append(char1 + 'X')
            i += 1
    return prepared

def encrypt(text, key):
    matrix = create_matrix(key)
    pairs = prepare_text(text)
    ciphertext = []

    for pair in pairs:
        r1, c1 = find_position(matrix, pair[0])
        r2, c2 = find_position(matrix, pair[1])

        if r1 == r2: # Same row: shift right
            ciphertext.append(matrix[r1][(c1 + 1) % 5])
            ciphertext.append(matrix[r2][(c2 + 1) % 5])
        elif c1 == c2: # Same column: shift down
            ciphertext.append(matrix[(r1 + 1) % 5][c1])
            ciphertext.append(matrix[(r2 + 1) % 5][c2])
        else: # Rectangle rule: swap columns
            ciphertext.append(matrix[r1][c2])
            ciphertext.append(matrix[r2][c1])

    return "".join(ciphertext)

# --- Testing ---
key = "MONARCHY"
plaintext = "Do you like to study cryptography course"

cipher_result = encrypt(plaintext, key)

print(f"Key: {key}")
print(f"Plaintext: {plaintext}")
print(f"Ciphertext: {cipher_result}")