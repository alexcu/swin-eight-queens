 #include <stdio.h>

// Create a new struct/record type; call it string
typedef struct string
{
  char str[256]; // a string contains 255 characters + EOString (null) char
} string;


// Read string function; returns a string read from console
string read_string(const char *prompt) //*prompt = pointer to a char
{	
	string input; // 'Input' variable of string type
	printf("%s", prompt);
	
	// UNDERSTANDING SCANF!!!! :D
	// Specifiy what to read: 
	// the space at the start is very important!!!!!
	// % = read something in and store into a varibale
	// [ ] = what do I want to read? --> " %[abc]" means I can only read characters a, b, c (abba but NOT -A-bbaDa)
		// ^ = not
		// so read up 255 characters that ARE NOT \n (End of Line char) 
		// as soon as I read \n, I will stop.
	// 255 not 256 because we need to read the \n (the sentinel in C strings) since the ^\n says stop reading @ \n
	// the space means >>skip (not stop at (not in [^ ]))<< any whitespace charcters 

	scanf(" %255[^\n]", input.str); // Scans for 255 characters of input
	return input;
}

// Read Integer
int read_integer(const char *prompt)
{
	string input;
	int num;
	char temp; // check if nothing comes after the int (EOString null char)

	input = read_string(prompt);

	// Scan the string, store number in num (and EOString null char in temp)
	// sscanf = string scan (formatted - i.e. %d (integer), %c (char), %lf (long float - double) etc.)
	// Must use pointers in flags in the scanf!!!
	while ( sscanf((input.str), " %d %c", &num, &temp) != 1 )
	{
		// Scan a number followed by something... so it's not a whole number
		printf("Enter a whole number! \n");
		input = read_string(prompt);
	}

	return num;
}

// Read Double
double read_double(const char *prompt)
{
	string input;
	double num;
	char temp;

	input = read_string(prompt);

	while ( sscanf((input.str), " %lf %c", &num, &temp) != 1 )
	{
		printf("Enter a whole number! \n");
		input = read_string(prompt);
	}

	return num;
}

// Read Integer Range
int read_integer_range(const char *prompt, int min, int max)
{
	int input;
	input = read_integer(prompt);

	// While integer is not in the range
	while ( !( (input > min) && (input < max) ))
	{
		// Reject the user input
		printf("That is outside the range of %d and %d \n", min, max);
		input = read_integer(prompt);
	}

	return input;
}

// Read Double Range
double read_double_range(const char *prompt, double min, double max)
{
	double input;
	input = read_double(prompt);

	// While integer is not in the range
	while ( !( (input > min) && (input < max) ))
	{
		// Reject the user input
		printf("That is outside the range of %lf and %lf \n", min, max);
		input = read_double(prompt);
	}

	return input;
}