#include <stdio.h>
#include <fcntl.h>  // For open
#include <unistd.h> // For read, write, and close

int main(int argc, char **argv)
{
	int i = 0;
	int f1, f2;
	char c, strin[100];

	// 🟢 Step 1: Open the file to write
	f1 = open("data", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (f1 < 0) {
		perror("Error opening file for writing");
		return 1;
	}

	// 📝 Step 2: Take input from the user
	printf("Type something: ");
	while (i < 99 && (c = getchar()) != '\n' && c != EOF) {
		strin[i++] = c;
	}
	strin[i] = '\0'; // Null-terminate the string

	// ✍️ Step 3: Write to the file
	if (write(f1, strin, i) < 0) {
		perror("Error writing to file");
		close(f1);
		return 1;
	}
	close(f1);

	// 📖 Step 4: Open the file for reading
	f2 = open("data", O_RDONLY);
	if (f2 < 0) {
		perror("Error opening file for reading");
		return 1;
	}

	// 🧠 Step 5: Read the file content
	ssize_t bytesRead = read(f2, strin, 99);
	if (bytesRead < 0) {
		perror("Error reading file");
		close(f2);
		return 1;
	}
	strin[bytesRead] = '\0'; // Null-terminate the read content

	// 👀 Final: Show the result
	printf("\nHere's what you typed:\n%s\n", strin);
	close(f2);

	return 0;
}


/*
 * steps: 
 * 1. open the notepad to write on it
 * 2. take input from the user
 * 3. write what the user typed 
 * 4. open the notepad to read from it
 * 5. read what is written on the file(aka notepad)
 */

