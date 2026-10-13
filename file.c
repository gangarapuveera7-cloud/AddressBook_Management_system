#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

// Saves all contacts to contacts.csv
void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.csv", "w");
    if (fp == NULL) return;
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp, "%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    fclose(fp);
}


// Loads all contacts from contacts.csv into the address book
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "r"); // open csv file
    if (file == NULL) return; // if file not exist, return

    char line[200]; // buffer for each line
    addressBook->contactCount = 0; // reset count

    while (fgets(line, sizeof(line), file)) { // read line by line

        // --- YOUR CODE STARTS HERE ---
        char *firstComma = strchr(line, ','); // find first comma
        if (!firstComma) continue; // skip invalid line
        *firstComma = '\0'; // split
        char *cName = line; // name part

        char *secondComma = strchr(firstComma+1, ','); // find second comma
        if (!secondComma) continue; // skip invalid
        *secondComma = '\0'; // split
        char *cPhone = firstComma+1; // phone part
        char *cEmail = secondComma+1; // email part
        cEmail[strcspn(cEmail, "\n")] = '\0'; // remove \n from email

        strcpy(addressBook->contacts[addressBook->contactCount].name, cName);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, cPhone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, cEmail);
        addressBook->contactCount++; // increment
        // --- YOUR CODE ENDS HERE ---
    }
    fclose(file); // close file
}
