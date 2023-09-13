#include <stdio.h>
#include <stdlib.h>

// Function to open the file
FILE *openFile(const char *fileName) {
  // Open the file in read mode
  FILE *fp = fopen(fileName, "r");

  // Check if the file was opened successfully
  if (fp == NULL) {
    printf("Error opening file: %s\n", fileName);
    exit(1);
  }

  return fp;
}

// Function to close the file
void closeFile(FILE *fp) {
  // Close the file
  fclose(fp);
}

// Function to read a line from the file
char *readLine(FILE *fp) {
  // Allocate a buffer to store the line
  char *line = malloc(100 * sizeof(char));

  // Read the line from the file
  fgets(line, 100, fp);

  // Remove the newline character from the end of the line
  line[strcspn(line, "\n")] = '\0';

  return line;
}

// Function to print the menu
void printMenu() {
  printf("1. Add ice cream flavor\n");
  printf("2. Remove ice cream flavor\n");
  printf("3. List all ice cream flavors\n");
  printf("4. Exit\n");
}

// Function to add an ice cream flavor
void addIceCreamFlavor(FILE *fp) {
  // Get the ice cream flavor from the user
  char flavor[100];
  printf("Enter the ice cream flavor: ");
  scanf("%s", flavor);

  // Write the ice cream flavor to the file
  fprintf(fp, "%s\n", flavor);
}

// Function to remove an ice cream flavor
void removeIceCreamFlavor(FILE *fp) {
  // Get the ice cream flavor from the user
  char flavor[100];
  printf("Enter the ice cream flavor to remove: ");
  scanf("%s", flavor);

  // Find the ice cream flavor in the file
  char *line;
  while ((line = readLine(fp)) != NULL) {
    if (strcmp(line, flavor) == 0) {
      // Remove the line from the file
      fseek(fp, -strlen(line) - 1, SEEK_CUR);
      fputc('\n', fp);
      break;
    }
  }
}

// Function to list all ice cream flavors
void listIceCreamFlavors(FILE *fp) {
  // Read all the lines from the file
  char *line;
  while ((line = readLine(fp)) != NULL) {
    printf("%s\n", line);
  }
}

int main() {
  // Open the file
  FILE *fp = openFile("ice_cream_flavors.txt");

  // Print the menu
  printMenu();

  // Get the user's choice
  int choice;
  scanf("%d", &choice);

  // Switch on the user's choice
  switch (choice) {
    case 1:
      addIceCreamFlavor(fp);
      break;
    case 2:
      removeIceCreamFlavor(fp);
      break;
    case 3:
      listIceCreamFlavors(fp);
      break;
    case 4:
      // Exit the program
      break;
    default:
      printf("Invalid choice\n");
      break;
  }

  // Close the file
  closeFile(fp);

  return 0;
}
