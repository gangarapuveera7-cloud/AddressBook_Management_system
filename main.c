/*
Name          :Gangarapu Veera Shankar
Batch ID      :26018F
Project Name  :Address Book Management System (C)
Description   :A menu-driven C program to create, search, edit, delete and list contacts using
               Structure & Array of Structures, with all data persistently stored in contacts.csv. 
               It uses Bubble Sort to list contacts by Name/Phone/Email.
*/
#include <stdio.h>
#include "contact.h"
#include "file.h"

// Program starts here
int main() {
    // choice stores the menu option entered by the user
    int choice;
    // The address book that holds all the contacts
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    // Show the main menu until the user chooses Exit
    do {
        // Print the main menu options
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        // Read the menu option
        scanf("%d", &choice);
        
        // Call the function for the chosen option
        switch (choice) {
            // Add a new contact
            case 1:
                createContact(&addressBook);
                break;
            // Search for a contact
            case 2:
                searchContact(&addressBook);
                break;
            // Edit an existing contact
            case 3:
                editContact(&addressBook);
                break;
            // Delete a contact
            case 4:
                deleteContact(&addressBook);
                break;
            // Ask how the contact list should be sorted, then list the contacts
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                // Stores the sort option entered by the user
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            // Exit option, the loop ends after this
            case 6:
                 printf("Saving and Exiting...\n");
                 saveAndExit(&addressBook); // <-- ADD THIS LINE
                 break;
            // Any other number is invalid
            default:
                printf("Invalid choice. Please try again.\n");
        }
    // Repeat the menu until option 6 is chosen
    } while (choice != 6);
    
       // End of the program
       return 0;
}
