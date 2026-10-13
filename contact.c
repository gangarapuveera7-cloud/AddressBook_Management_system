#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

// Displays all contacts after sorting them by the chosen field
void listContacts(AddressBook *addressBook, int sortCriteria) {
    // Sort contacts based on the chosen criteria
    // Stop if the address book is empty
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts to display.\n");
        return;
    }

    // Stop if the sort option is not 1, 2 or 3
    if (sortCriteria < 1 || sortCriteria > 3) 
    {
        printf("Invalid sort criteria! Use 1.Name 2.Phone 3.Email\n");
        return;
    }

    // Bubble Sort based on sortCriteria
    // Outer loop of bubble sort: number of passes
    for (int i = 0; i < addressBook->contactCount - 1; i++) 
    {
        // Inner loop: compare each pair of neighbouring contacts
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) 
        {
            // Holds the comparison result of the two contacts
            int cmp = 0;
            // Compare by name, phone or email based on the sort option
            if (sortCriteria == 1)
                cmp = strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name);
            else if (sortCriteria == 2)
                cmp = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone);
            else if (sortCriteria == 3)
                cmp = strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email);

            if (cmp > 0) // swap for ascending order
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }

    // Print the list heading with the total contact count
    printf("\n--- Contact List (%d contacts) ---\n", addressBook->contactCount);
    // Print the table column headings
    printf("%-6s %-25s %-15s %-30s\n", "Sl No", "Name", "Phone", "Email");
    // Print a separator line
    printf("----------------------------------------------------------------------------------------\n");
    // Print every contact with its serial number
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-6d %-25s %-15s %-30s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    // Print the closing separator line
    printf("----------------------------------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook) {
    // Start with zero contacts
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    // Read saved contacts from the file into the address book
    loadContactsFromFile(addressBook);
}

// Saves the contacts to the file and terminates the program
void saveAndExit(AddressBook *addressBook) {
    // Write all contacts to the file
    saveContactsToFile(addressBook); 
    // Close the program successfully
    exit(EXIT_SUCCESS);
}

// Creates a new contact after validating name, phone and email
void createContact(AddressBook *addressBook){
	// Define the logic to create a Contacts
   // Do not add if the address book has reached its maximum size
   if (addressBook->contactCount >= MAX_CONTACTS) 
   {
        printf("Address Book is full!\n");
        return;
    }
    // Temporary buffers to hold the user input
    char name[50], phone[20], email[50];

    // Repeat until a valid name is entered
    while (1) 
    {
        // Ask the user for the name
        printf("Enter Name: ");
        // Read the full name including spaces (max 49 characters)
        scanf(" %49[^\n]", name);
        // Find the length of the entered name
        int len = strlen(name);
        // Flag to track whether the name is valid
        int valid = 1;

        // Name must have at least 3 characters
        if (len < 3) 
        {
            printf("Error Message : Name must contain at least 3 characters\n");
            continue;
        }
        // Check every character of the name
        for (int i = 0; i < len; i++) 
        {
            char c = name[i];
            // Spaces are allowed in the name
            if (c == ' ') 
            continue;
            // Digits are not allowed in the name
            if (c >= '0' && c <= '9') 
            {
                printf("Error Message : Numbers are not allowed in the name\n");
                valid = 0; break;
            }
            // Only alphabets are allowed in the name
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) 
            {
                printf("Error Message : Name should contain only alphabets\n");
                valid = 0; 
                break;
            }
        }
        // Exit the loop when the name is valid
        if (valid) 
        break;
    }

    // Repeat until a valid phone number is entered
    while (1) 
    {
        // Ask the user for the phone number
        printf("Enter Phone: ");
        // Read the phone number (max 19 characters)
        scanf(" %19[^\n]", phone);
        int len = strlen(phone);
        int valid = 1;

        // Check that every character is a digit
        for (int i = 0; i < len; i++) 
        {
            if (phone[i] < '0' || phone[i] > '9') 
            {
                printf("Error Message : Phone number should contain only digits\n");
                valid = 0; 
                break;
            }
        }
        // Ask again if a non-digit was found
        if (!valid) 
        continue;

        // Phone number must be exactly 10 digits
        if (len!= 10) 
        {
            printf("Error Message : Phone number must contain exactly 10 digits\n");
            continue;
        }
        // Check that the phone number is not already saved
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
            {
                printf("Error Message : Phone number Must be Unique\n");
                valid = 0; 
                break;
            }
        }
        // Exit the loop when the phone number is valid
        if (valid) 
        break;
    }

    // Repeat until a valid email is entered
    while (1) 
    {
        // Ask the user for the email
        printf("Enter Email: ");
        // Read the email (max 49 characters)
        scanf(" %49[^\n]", email);
        int len = strlen(email);
        // Variables to count and locate the @ and . symbols
        int atCount = 0, atPos = -1, dotCount = 0, dotPos = -1;
        int valid = 1;

        // Count the @ symbols and remember the last position
        for (int i = 0; i < len; i++) 
        if (email[i] == '@') 
        { 
            atCount++; atPos = i; 
        }
        // Count the dots and remember the last position
        for (int i = 0; i < len; i++) 
        if (email[i] == '.') 
        { 
            dotCount++; dotPos = i; 
        }

        // Check that the email is not already saved
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            if (strcmp(addressBook->contacts[i].email, email) == 0) 
            {
                printf("Error Message : Email ID Must be Unique\n");
                valid = 0; 
                break;
            }
        }
        // Ask again if the email already exists
        if (!valid) 
        continue;

        // Email must contain an @ symbol
        if (atCount == 0) 
        { 
            printf("Error Message : Missing @\n"); 
            continue; 
        }
        // Email must not contain more than one @
        if (atCount > 1) 
        { 
            printf("Error Message : Multiple @ symbols are not allowed\n"); 
            continue; 
        }
        // Email must contain exactly one dot
        if (dotCount!= 1) 
        { 
            printf("Error Message : Email ID must contain exactly one. (dot)\n"); 
            continue; 
        }

        // Only lowercase letters, digits, @ and . are allowed
        for (int i = 0; i < len; i++) 
        {
            char c = email[i];
            if (c == '@' || c == '.') 
            continue;
            if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) 
            {
                printf("Error Message : Invalid symbol\n");
                valid = 0; 
                break;
            }
        }
        if (!valid) 
        continue;

        // The dot must come after the @ symbol
        if (dotPos < atPos) 
        { 
            printf("Error Message : The. (dot) must appear after @ symbol\n"); 
            continue; 
        }
        // At least one character is needed between @ and the dot
        if (dotPos - atPos <= 1) 
        { 
            printf("Error Message : There must be at least one character between @ and. (dot)\n");
             continue; 
        }
        // Email must end with .com and nothing after it
        if (len < 4 || strcmp(email + len - 4, ".com")!= 0 || dotPos!= len - 4) 
        {
            printf("Error Message : Extra characters after the domain\n");
            continue;
        }
        // Email is valid, so leave the loop
        break;
    }

    // Copy the validated name, phone and email into the next free slot
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    // Increase the contact count by one
    addressBook->contactCount++;
    // Confirm to the user that the contact is added
    saveContactsToFile(addressBook); // <-- ADD THIS
    printf("Contact Added Successfully! Saved to contacts.csv\n");

}

// Searches contacts by name, phone or email
void searchContact(AddressBook *addressBook) {
    // Define the logic for search
    int choice;
    char key[50];
    // Stores the positions of all matching contacts
    int matchIndex[100];
    // Number of matches found
    int matchCount;

    // Keep showing the menu until a search is done or the user exits
    do {
        // Reset the match counter for every search
        matchCount = 0;
        // Show the search menu
        printf("\n--- Search Menu ---\n");
        printf("1. Search by Name\n");
        printf("2. Search by Phone\n");
        printf("3. Search by Email\n");
        printf("4. Exit to Main Menu\n");
        printf("Enter your choice: ");
        // Read the user's menu choice
        scanf("%d", &choice);

        // Option 4 goes back to the main menu
        if (choice == 4) 
        return; 

        // Reject choices outside 1 to 4
        if (choice < 1 || choice > 4) {
            printf("Invalid choice! Enter 1-4.\n");
            continue;
        }

        // Ask for the value to search
        printf("Enter value to search: ");
        // Read the search text (max 49 characters)
        scanf(" %49[^\n]", key);

        // Go through all contacts and save the positions that match
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            // Name search matches any part of the name
            if (choice == 1 && strstr(addressBook->contacts[i].name, key))
                matchIndex[matchCount++] = i;
            // Phone search needs an exact match
            else if (choice == 2 && strcmp(addressBook->contacts[i].phone, key) == 0)
                matchIndex[matchCount++] = i;
            // Email search needs an exact match
            else if (choice == 3 && strcmp(addressBook->contacts[i].email, key) == 0)
                matchIndex[matchCount++] = i;
        }

        // Show a message if nothing matched
        if (matchCount == 0) 
        {
            printf("Contact Not Found!\n"); 
            continue;
        }

        // Show how many contacts were found
        printf("\nFound %d contact(s):\n", matchCount);
        // Print every matching contact
        for (int i = 0; i < matchCount; i++) 
        {
            int idx = matchIndex[i];
            printf("%d. %s | %s | %s\n", i+1, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
        }
        // Search finished, return to the main menu
        return;

    } while(1);
}

// Edits the name, phone or email of an existing contact
void editContact(AddressBook *addressBook){
    // choice is the search option, field is the item to edit
    int choice, field;
    char key[50];
    // Stores the positions of all matching contacts
    int matchIndex[100];
    int matchCount;

    // Keep showing the menu until an edit is done or the user exits
    do {
        matchCount = 0;
        // Show the edit menu
        printf("\n--- Edit Menu ---\n");
        printf("1. Edit by Name\n2. Edit by Phone\n3. Edit by Email\n4. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Option 4 goes back to the main menu
        if (choice == 4) 
        return; 

        // Reject choices outside 1 to 4
        if (choice < 1 || choice > 4) 
        {
            printf("Invalid choice! Enter 1-4.\n");
            continue;
        }

        // Ask for the value used to find the contact
        printf("Enter value to search: ");
        scanf(" %49[^\n]", key);

        // Go through all contacts and save the positions that match
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            if (choice == 1 && strstr(addressBook->contacts[i].name, key))
                matchIndex[matchCount++] = i;
            else if (choice == 2 && strcmp(addressBook->contacts[i].phone, key) == 0)
                matchIndex[matchCount++] = i;
            else if (choice == 3 && strcmp(addressBook->contacts[i].email, key) == 0)
                matchIndex[matchCount++] = i;
        }

        // Show a message if nothing matched
        if (matchCount == 0) 
        {
            printf("Contact Not Found!\n");
            continue;
        }

        // Position of the contact to be edited
        int editPos = -1;
        // Only one match, so edit it directly
        if (matchCount == 1) 
        {
            editPos = matchIndex[0];
        } else 
        {
            // More than one match, so the user must pick one
            printf("\nMultiple matching records found:\n");
            for (int i = 0; i < matchCount; i++) 
            {
                int idx = matchIndex[i];
                printf("%d. %s | %s | %s\n", i+1, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
            }
            int sel;
            // Ask which record to edit
            printf("Select one record to edit (1-%d): ", matchCount);
            scanf("%d", &sel);
            // Reject a selection outside the list
            if (sel < 1 || sel > matchCount) 
            {
                printf("Invalid selection!\n");
                continue;
            }
            // Save the position of the selected contact
            editPos = matchIndex[sel-1];
        }

        // Show the contact that is being edited
        printf("\nEditing: %s | %s | %s\n", addressBook->contacts[editPos].name, addressBook->contacts[editPos].phone, addressBook->contacts[editPos].email);
        // Ask which field to edit
        printf("1. Edit Name\n2. Edit Phone\n3. Edit Email\n4. Edit All\n5. Exit\nEnter choice: ");
        scanf("%d", &field);

        // Option 5 exits without editing
        if (field == 5) 
        return;

        // Copy the old values so unchanged fields stay the same
        char newName[50], newPhone[20], newEmail[50];
        strcpy(newName, addressBook->contacts[editPos].name);
        strcpy(newPhone, addressBook->contacts[editPos].phone);
        strcpy(newEmail, addressBook->contacts[editPos].email);
        
        // Read and validate the new name
        if (field == 1 || field == 4) 
        {
            printf("Enter New Name: ");
            scanf(" %49[^\n]", newName);
            int ok = 1;
            // Name must have only alphabets and spaces
            for(int k=0; newName[k]; k++) 
            if(!isalpha(newName[k]) && newName[k]!=' ') 
            ok=0;
            if(!ok || strlen(newName)==0)
            {
                printf("Invalid Name! Only alphabets and spaces allowed.\n");
                continue;
            }
        }
        // Read and validate the new phone number
        if (field == 2 || field == 4) 
        {
            printf("Enter New Phone: ");
            scanf(" %19[^\n]", newPhone);
            int ok = 1;
            // Phone number must be exactly 10 digits
            if(strlen(newPhone)!=10) 
            ok=0;
            // Every character must be a digit
            for(int k=0; newPhone[k]; k++) 
            if(!isdigit(newPhone[k])) 
            ok=0;
            if(!ok) 
            {
                printf("Invalid Phone! Must be 10 digits.\n");
                continue;
            }
        }
        // Read and validate the new email
        if (field == 3 || field == 4) 
        {
            printf("Enter New Email: ");
            scanf(" %49[^\n]", newEmail);
            // Find the first @ and the last dot in the email
            char *at = strchr(newEmail,'@');
            char *dot = strrchr(newEmail,'.');
            // Email needs an @ and a dot after it
            if(!at ||!dot || dot<at) 
            {
                printf("Invalid Email! Must contain @ and.\n");
                continue;
            }
        }

        // Save the new values into the contact
        strcpy(addressBook->contacts[editPos].name, newName);
        strcpy(addressBook->contacts[editPos].phone, newPhone);
        strcpy(addressBook->contacts[editPos].email, newEmail);
        // Confirm to the user that the contact is updated
        saveContactsToFile(addressBook);
        printf("Contact Updated Successfully!\n");
        return;

    } while(1);
}

// Deletes a contact after asking for confirmation
void deleteContact(AddressBook *addressBook){
	// Define the logic for deletecontact
   // choice is the delete option chosen by the user
   int choice;
    char key[50];
    // Stores the positions of all matching contacts
    int matchIndex[MAX_CONTACTS];
    int matchCount = 0;

    // Keep showing the menu until a delete is done or the user exits
    do {
        
        // Show the delete menu
        printf("\n--- Delete Menu ---\n");
        printf("1. Delete by Name\n");
        printf("2. Delete by Phone\n");
        printf("3. Delete by Email\n");
        printf("4. Exit to Main Menu\n");
        printf("Enter your choice: ");
        // Read the user's menu choice
        scanf("%d", &choice);

        // Reset the match counter for every search
        matchCount = 0;

        // Handle the chosen delete option
        switch (choice) 
        {
            // Delete by name
            case 1:
                printf("Enter Name to Delete: ");
                scanf(" %49[^\n]", key);
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strstr(addressBook->contacts[i].name, key)!= NULL) 
                    {
                        matchIndex[matchCount++] = i;
                    }
                }
                break;
            // Delete by phone
            case 2:
                printf("Enter Phone to Delete: ");
                scanf(" %19[^\n]", key);
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(addressBook->contacts[i].phone, key) == 0) 
                    {
                        matchIndex[matchCount++] = i;
                    }
                }
                break;
            // Delete by email
            case 3:
                printf("Enter Email to Delete: ");
                scanf(" %49[^\n]", key);
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strcmp(addressBook->contacts[i].email, key) == 0) 
                    {
                        matchIndex[matchCount++] = i;
                    }
                }
                break;
            // Go back to the main menu
            case 4:
                printf("Exiting delete menu...\n");
                return;
            // Invalid option, show the menu again
            default:
                printf("Invalid choice! Please enter valid choice (1-4).\n");
                continue;
        }

        // Stop if no contact matched
        if (matchCount == 0) {
            printf("Contact Not Found!\n");
            return;
        }
        // Position of the contact to be deleted
        int deletePos = -1;
        // Only one match, so show it directly
        if (matchCount == 1) 
        {
            deletePos = matchIndex[0];
            printf("\nContact Found: %s | %s | %s\n", addressBook->contacts[deletePos].name, addressBook->contacts[deletePos].phone, addressBook->contacts[deletePos].email);
        } 
        // More than one match, so the user must pick one
        else 
        {
            printf("\nMultiple records found:\n");
            for (int i = 0; i < matchCount; i++) 
            {
                int idx = matchIndex[i];
                printf("%d. %s | %s | %s\n", i+1, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
            }
            // Add an option to cancel the delete
            printf("%d. Exit\n", matchCount+1);
            int sel;
            printf("Select the record to delete (1-%d): ", matchCount+1);
            scanf("%d", &sel);
            // Cancel if the user selects Exit or an invalid number
            if (sel == matchCount+1 || sel <=0 || sel > matchCount+1) 
            {
                printf("Delete cancelled.\n");
                return;
            }
            deletePos = matchIndex[sel-1];
        }
        
        // Ask for confirmation before deleting
        char confirm;
        printf("Are you sure you want to delete? (Y/N): ");
        scanf(" %c", &confirm);
        // Delete only when the user enters Y or y
        if (confirm == 'Y' || confirm == 'y') 
        {
            // Shift all later contacts one place up to fill the gap
            for (int j = deletePos; j < addressBook->contactCount - 1; j++) 
            {
                addressBook->contacts[j] = addressBook->contacts[j+1];
            }
            // Reduce the contact count by one
            addressBook->contactCount--;
            saveContactsToFile(addressBook);
            printf("Contact Deleted Successfully!\n");
        // User did not confirm, so nothing is deleted
        } else {
            printf("Delete operation cancelled!\n");
        }
        return;

    } while (1);
}
