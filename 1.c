#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MX 5

void playfair(char ch1, char ch2, char key[MX][MX])
{
    int i, j, w, x, y, z;
    FILE *out;

    if ((out = fopen("cipher.txt", "a+")) == NULL)
    {
        printf("Error opening file.");
        return;
    }

    for (i = 0; i < MX; i++)
    {
        for (j = 0; j < MX; j++)
        {
            if (ch1 == key[i][j])
            {
                w = i;
                x = j;
            }
            else if (ch2 == key[i][j])
            {
                y = i;
                z = j;
            }
        }
    }

    if (w == y)
    {
        x = (x + 1) % MX;
        z = (z + 1) % MX;
        printf("%c%c", key[w][x], key[y][z]);
        fprintf(out, "%c%c", key[w][x], key[y][z]);
    }
    else if (x == z)
    {
        w = (w + 1) % MX;
        y = (y + 1) % MX;
        printf("%c%c", key[w][x], key[y][z]);
        fprintf(out, "%c%c", key[w][x], key[y][z]);
    }
    else
    {
        printf("%c%c", key[w][z], key[y][x]);
        fprintf(out, "%c%c", key[w][z], key[y][x]);
    }

    fclose(out);
}

int main()
{
    int i, j, k = 0, m = 0, n;
    char key[MX][MX], keystr[25], str[100];

    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K',
                         'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                         'V', 'W', 'X', 'Y', 'Z'};

    printf("Enter key (max 25 characters): ");
    scanf("%s", keystr);

    printf("Enter the plain text (max 100 characters): ");
    scanf(" %[^\n]s", str);

    n = strlen(keystr);

    // Convert key to uppercase
    for (i = 0; i < n; i++)
    {
        keystr[i] = toupper(keystr[i]);
        if (keystr[i] == 'J')
            keystr[i] = 'I';
    }

    // Convert plaintext to uppercase
    for (i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
        if (str[i] == 'J')
            str[i] = 'I';
    }

    // Fill the key matrix
    int used[26] = {0};
    for (i = 0; i < n; i++)
    {
        if (keystr[i] == 'J')
            keystr[i] = 'I';
        if (!used[keystr[i] - 'A'])
        {
            key[m / MX][m % MX] = keystr[i];
            used[keystr[i] - 'A'] = 1;
            m++;
        }
    }

    for (i = 0; i < 26; i++)
    {
        if (alphabet[i] == 'J')
            continue;
        if (!used[alphabet[i] - 'A'])
        {
            key[m / MX][m % MX] = alphabet[i];
            used[alphabet[i] - 'A'] = 1;
            m++;
        }
    }

    // Print the key matrix
    printf("\nKey Matrix:\n");
    for (i = 0; i < MX; i++)
    {
        for (j = 0; j < MX; j++)
        {
            printf("%c ", key[i][j]);
        }
        printf("\n");
    }

    // Encrypt the plaintext
    printf("\nEntered text: %s\nCipher Text: ", str);
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'J')
            str[i] = 'I';
        if (str[i + 1] == '\0')
            playfair(str[i], 'X', key);
        else
        {
            if (str[i] == str[i + 1])
                playfair(str[i], 'X', key);
            else
            {
                playfair(str[i], str[i + 1], key);
                i++;
            }
        }
    }

    return 0;
}