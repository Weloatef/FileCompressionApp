/*To Do List :-
1- free (filedestenation)*/

#include <stdio.h>  
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

struct holder {
	char charecter;
	holder* next;
};
struct content {
	char c;
	int freq;
};

struct TreeNode {
	content data;
	TreeNode* left;
	TreeNode* right;
	TreeNode* Parent;
	TreeNode() {
		left = right = NULL;
	}
};
struct Node
{
	TreeNode tree;
	Node* next;
};
bool find(holder* h, char item) {
	if (h == NULL)
		return false;
	while (h->next != NULL) {
		if (h->charecter == item)
			return true;
		else
			h = h->next;
	}
	if (h->charecter == item)
		return true;
	return false;
}
holder* insert(holder* h, char item)
{
	if (h == NULL)
	{
		h = (holder*)malloc(sizeof(holder));
		h->charecter = item;
		h->next = NULL;
	}
	else
	{
		holder* it = h;
		while (it->next != NULL)
			it = it->next;

		holder* tmp = (holder*)malloc(sizeof(holder));
		tmp->charecter = item;
		tmp->next = NULL;
		it->next = tmp;
	}

	return h;
}
Node* Insert_Ascending(Node* h, int freq, char item) {
	if (h == NULL) {
		h = (Node*)malloc(sizeof(Node));
		h->tree.data.c = item;
		h->tree.data.freq = freq;
		h->tree.left = NULL;
		h->tree.right = NULL;
		h->tree.Parent = NULL;
		h->next = NULL;

	}
	else {
		if (h->tree.data.freq <= freq) {
			Node* it = h;
			while (it->next != NULL) {
				if (it->next->tree.data.freq <= freq)
					it = it->next;
				else {
					Node* tmp = (Node*)malloc(sizeof(Node));;
					tmp->tree.data.c = item;
					tmp->tree.data.freq = freq;
					tmp->tree.left = NULL;
					tmp->tree.right = NULL;
					tmp->tree.Parent = NULL;
					tmp->next = it->next;
					it->next = tmp;
					break;
				}
			}
			if (it->next == NULL) {
				Node* tmp = (Node*)malloc(sizeof(Node));;
				tmp->tree.data.c = item;
				tmp->tree.data.freq = freq;
				tmp->tree.left = NULL;
				tmp->tree.right = NULL;
				tmp->tree.Parent = NULL;
				tmp->next = NULL;
				it->next = tmp;
			}
		}
		else {
			Node* tmp = (Node*)malloc(sizeof(Node));;
			tmp->tree.data.c = item;
			tmp->tree.data.freq = freq;
			tmp->tree.left = NULL;
			tmp->tree.right = NULL;
			tmp->tree.Parent = NULL;
			tmp->next = h;
			h = tmp;
		}
	}
	return h;
}
Node* Insert_Ascending2(Node* h, TreeNode* t1, TreeNode* t2) {//,TreeNode* t1out,TreeNode* t2out
	if (h == NULL) {
		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->tree.data.c = '^';
		tmp->tree.data.freq = t1->data.freq + t2->data.freq;
		tmp->tree.left = t1;
		tmp->tree.right = t2;
		tmp->tree.Parent = NULL;
		t1->Parent = t2->Parent /*= t1out = t2out*/ = &tmp->tree;
		tmp->tree.left->Parent = &tmp->tree;
		tmp->tree.right->Parent = &tmp->tree;
		tmp->next = NULL;
		h = tmp;
	}
	else {
		if (h->tree.data.freq <= t1->data.freq + t2->data.freq) {
			Node* it = h;
			while (it->next != NULL) {
				if (it->next->tree.data.freq <= t1->data.freq + t2->data.freq)
					it = it->next;
				else {
					Node* tmp = (Node*)malloc(sizeof(Node));;
					tmp->tree.data.c = '^';
					tmp->tree.data.freq = t1->data.freq + t2->data.freq;
					tmp->tree.left = t1;
					tmp->tree.right = t2;
					tmp->tree.Parent = NULL;
					t1->Parent = t2->Parent = &tmp->tree;
					tmp->next = it->next;
					tmp->tree.left->Parent = &tmp->tree;
					tmp->tree.right->Parent = &tmp->tree;
					it->next = tmp;
					break;
				}
			}
			if (it->next == NULL) {
				Node* tmp = (Node*)malloc(sizeof(Node));;
				tmp->tree.data.c = '^';
				tmp->tree.data.freq = t1->data.freq + t2->data.freq;
				tmp->tree.left = t1;
				tmp->tree.right = t2;
				tmp->tree.Parent = NULL;
				t1->Parent = &tmp->tree;
				t2->Parent = &tmp->tree;
				tmp->next = NULL;
				it->next = tmp;
			}
		}
		else {
			Node* tmp = (Node*)malloc(sizeof(Node));;
			tmp->tree.data.c = '^';
			tmp->tree.data.freq = t1->data.freq + t2->data.freq;
			tmp->tree.left = t1;
			tmp->tree.right = t2;
			tmp->tree.Parent = NULL;
			t1->Parent = &tmp->tree;
			t2->Parent = &tmp->tree;
			tmp->next = h;
			h = tmp;
		}
	}
	return h;
}
Node* removeFirst(Node* n, char* c, int* f) {
	if (n->next == NULL) {
		*c = n->tree.data.c;
		*f = n->tree.data.freq;
		free(n);
		n = (Node*)malloc(sizeof(Node));
	}
	else {
		Node* tmp = n;
		n = n->next;
		*c = tmp->tree.data.c;
		*f = tmp->tree.data.freq;
		free(tmp);
	}
	return n;
}


struct frequencyCodes {
	//This is used to store the codes for idividual characters//
	char character;
	char code[8];
};
void code(TreeNode* root, char* p, char* temp, char fileName[]) {
	//Creates the codes for letters from Huffman Tree
	if (!(root->Parent == NULL && root->left == root && root->right == root)) {

		if (root->left != NULL && root->left != root) {
			*temp = '0';
			temp++;
			code(root->left, p, temp, fileName);
		}
		if (root->right != NULL && root->right != root) {
			*temp = '1';
			temp++;
			code(root->right, p, temp, fileName);
		}
		if (root->left == NULL && root->right == NULL) {
			if (root->Parent->left == root)
				root->Parent->left = root->Parent;
			else
				root->Parent->right = root->Parent;
			FILE* f = fopen(fileName, "a");
			if (root->data.c == '0' || root->data.c == '1') {
				fprintf(f, "%d%s", root->data.c, p);
			}
			else
				fprintf(f, "%c%s", root->data.c, p);
			fclose(f);
			printf("%c:%s\n", root->data.c, p);
			*temp = '\0';
			temp--;
			code(root->Parent, p, temp, fileName);
		}
		if (root->left == root && root->right == root && root->Parent != NULL) {
			if (root->Parent->left == root)
				root->Parent->left = root->Parent;
			else
				root->Parent->right = root->Parent;
			*temp = '\0';
			temp--;
			code(root->Parent, p, temp, fileName);
		}
	}
}
struct decimalnum
{
	char data;
	decimalnum* next;
};
decimalnum* insertLast(decimalnum* h, char item)
{
	if (h == NULL)
	{
		h = (decimalnum*)malloc(sizeof(decimalnum));
		h->data = item;
		h->next = NULL;
	}
	else
	{
		decimalnum* it = h;
		while (it->next != NULL)
			it = it->next;

		decimalnum* tmp = (decimalnum*)malloc(sizeof(decimalnum));
		tmp->data = item;
		tmp->next = NULL;

		it->next = tmp;
	}

	return h;
}
void binarytodecimal(char s[], decimalnum** x, int* c)
{
	int z = 0;
	int k = 0;
	int l;
	int m;
	char p;
	char f;
	if (s[0] == '1')
	{
		l = 8;
		z = z + l;
	}
	if (s[1] == '1')
	{
		l = 4;
		z = z + l;
	}
	if (s[2] == '1')
	{
		l = 2;
		z = z + l;
	}
	if (s[3] == '1')
	{
		l = 1;
		z = z + l;
	}
	if (s[4] == '1')
	{
		l = 8;
		k = k + l;
	}
	if (s[5] == '1')
	{
		l = 4;
		k = k + l;
	}
	if (s[6] == '1')
	{
		l = 2;
		k = k + l;
	}
	if (s[7] == '1')
	{
		l = 1;
		k = k + l;
	}
	switch (z)
	{
	case 0:
		*x = insertLast(*x, '0');
		break;
	case 1:
		*x = insertLast(*x, '1');
		break;
	case 2:
		*x = insertLast(*x, '2');
		break;
	case 3:
		*x = insertLast(*x, '3');
		break;
	case 4:
		*x = insertLast(*x, '4');
		break;
	case 5:
		*x = insertLast(*x, '5');
		break;
	case 6:
		*x = insertLast(*x, '6');
		break;
	case 7:
		*x = insertLast(*x, '7');
		break;
	case 8:
		*x = insertLast(*x, '8');
		break;
	case 9:
		*x = insertLast(*x, '9');
		break;
	case 10:
		*x = insertLast(*x, 'A');
		break;
	case 11:
		*x = insertLast(*x, 'B');
		break;
	case 12:
		*x = insertLast(*x, 'C');
		break;
	case 13:
		*x = insertLast(*x, 'D');
		break;
	case 14:
		*x = insertLast(*x, 'E');
		break;
	case 15:
		*x = insertLast(*x, 'F');
		break;
	}
	*c = *c + 1;
	switch (k)
	{
	case 0:
		*x = insertLast(*x, '0');
		break;
	case 1:
		*x = insertLast(*x, '1');
		break;
	case 2:
		*x = insertLast(*x, '2');
		break;
	case 3:
		*x = insertLast(*x, '3');
		break;
	case 4:
		*x = insertLast(*x, '4');
		break;
	case 5:
		*x = insertLast(*x, '5');
		break;
	case 6:
		*x = insertLast(*x, '6');
		break;
	case 7:
		*x = insertLast(*x, '7');
		break;
	case 8:
		*x = insertLast(*x, '8');
		break;
	case 9:
		*x = insertLast(*x, '9');
		break;
	case 10:
		*x = insertLast(*x, 'A');
		break;
	case 11:
		*x = insertLast(*x, 'B');
		break;
	case 12:
		*x = insertLast(*x, 'C');
		break;
	case 13:
		*x = insertLast(*x, 'D');
		break;
	case 14:
		*x = insertLast(*x, 'E');
		break;
	case 15:
		*x = insertLast(*x, 'F');
		break;
	}
	*c = *c + 1;
}
void decode(char x[], char y[], char z[]) {
	bool myFlag = false;
	int i2, j2;
	for (int i = 0; i < strlen(x); i++) {
		char letter = NULL;
		for (int j = 0; j < strlen(y); j++) {
			if (y[j] != 48 && y[j] != 49) {
				if (y[j + 1] != 48 && y[j + 1] != 49) {
					if (y[j + 1] == '9') {
						letter = 49;
						j2 = j + 2;
						i2 = i;
						myFlag = false;
					}
					else {
						letter = 48;
						j2 = j + 2;
						i2 = i;
						myFlag = false;

					}
				}
				else {
					letter = y[j];
					j2 = j + 1;
					i2 = i;
					myFlag = false;
				}
				while (x[i2] == y[j2]) {
					if (y[j2 + 1] != 48 && y[j2 + 1] != 49) {
						myFlag = true;

					}
					i2++;
					j2++;
				}
				if (myFlag == true) {
					strncat(z, &letter, 1);

					i = i2 - 1;
					break;
				}
			}

		}
	}

}
void convertbin(char x[], char y[]) {
	for (int i = 0; i < strlen(x) + 1; i++) {
		if (x[i] == '0')strncat(y, "0000", 4);
		if (x[i] == '1')strncat(y, "0001", 4);
		if (x[i] == '2')strncat(y, "0010", 4);
		if (x[i] == '3')strncat(y, "0011", 4);
		if (x[i] == '4')strncat(y, "0100", 4);
		if (x[i] == '5')strncat(y, "0101", 4);
		if (x[i] == '6')strncat(y, "0110", 4);
		if (x[i] == '7')strncat(y, "0111", 4);
		if (x[i] == '8')strncat(y, "1000", 4);
		if (x[i] == '9')strncat(y, "1001", 4);
		if (x[i] == 'A')strncat(y, "1010", 4);
		if (x[i] == 'B')strncat(y, "1011", 4);
		if (x[i] == 'C')strncat(y, "1100", 4);
		if (x[i] == 'D')strncat(y, "1101", 4);
		if (x[i] == 'E')strncat(y, "1110", 4);
		if (x[i] == 'F')strncat(y, "1111", 4);

	}
}

int main()
{
	// to hold letters in used in making frequency table 
	holder* Letters_Holder = NULL;
	/*linked list to the frequency table contents :-
			1-character (to hold the charecter of type char)
			2- data (to hold the frequency value of type int)
			3-next ( to direct to another node )   */
	Node* Frequency_Table = NULL;

	struct stat ss;
	// pointer to hold the destenation of the file
	char* File_Destenation = (char*)malloc(sizeof(char) * 1000);
	// to hold the user input ( compress or extract )
	int choice;
	// under constracting
	char* extention;
	// to hold the file direction
	FILE* tf = NULL;
	FILE* tf2 = NULL;
	// to hold the current charecter we are working on (used in making the frequency table)
	char current, current2;
	// to hold the value of the frequecy of the current letter 
	int freq = 0;
	char defaul[4] = { '.','t','x','t' };
	int flag = 0, length, flag2 = 0;
	// this part used to get the file destenation and open it and check it's validation 
	while (tf == NULL) {
		printf("\n\t\t\t\t\tHello\n To start conversion please type your file destenation here :- ");
		scanf("%s", File_Destenation);
		tf = fopen(File_Destenation, "r+");
		//extention = strchr(File_Destenation, '.');
		if (tf == NULL)
			printf("File Not found Please try again");
		/*else if (extention != "txt") {
			printf("\nFile type must be text please try again !! ");
			tf = NULL;
		}*/
		else {
			stat(File_Destenation, &ss);
			extention = strrchr(File_Destenation, '.');
			if (ss.st_size > 2147483628) {
				tf = NULL;
				printf("The file is larger than 2 gigabyte please choose another file");
			}
			if (extention != NULL) {
				length = strlen(extention);
				for (int i = 0; i < length; i++) {
					if (extention[i] != defaul[i])
						flag = 1;
				}
				if (flag == 1) {
					printf("\nFile type must be text please try again !! ");
					tf = NULL;
				}
			}
			else {
				printf("\nNo File Extention please try again");
				tf = NULL;
			}
		}
		
		if (tf != NULL) {
			for (int x = 0; x <= length; x++) {
				fscanf(tf, "%c", &current);
				int d = current;
				if (d > 127 || d < 0)
					flag2 = 1;
			}
			if (flag2 == 1) {
				printf("\nThis File contain Non-ascii character !! please try again");
				tf = NULL;
			}
			else {
				current = NULL;
				fseek(tf, 0, SEEK_SET);
				//tf = fopen(File_Destenation, "r+");
			}
		}
	}
	// this part to choose what you want to do compress or extract 
	printf("\nplease chosse :-  \n 1- Compress ( Enter 1 ) \n 2- Extract ( Enter 2 ) \n 3- End (Enter 3) \n");
	scanf("%d", &choice);
	// this part used in making the frequency table
	do {
		if (choice == 1) {
			holder* hold = NULL;
			tf2 = fopen(File_Destenation, "r+");
			while (ftell(tf) < ss.st_size) {
				fscanf(tf, "%c", &current);
				if (find(Letters_Holder, current) == false) {
					Letters_Holder = insert(Letters_Holder, current);
					while (ftell(tf2) < ss.st_size)
					{
						fscanf(tf2, "%c", &current2);
						if (current == current2)
							freq++;
					}
					fseek(tf2, 0, SEEK_SET);
					Frequency_Table = Insert_Ascending(Frequency_Table, freq, current);
					freq = 0;
				}
			}
			free(hold);
			//---------------Extracting File Name--------------//
			char fileNamecod[1000] = "";
			char filenamecom[1000] = "";
			strcat(fileNamecod, File_Destenation);
			int size = strlen(File_Destenation);
			char* file = &fileNamecod[size];
			for (int i = size; *file != '.'; i--, file--) {
				*file = '\0';
			}
			*file = '\0';
			strcpy(filenamecom, fileNamecod);
			strcat(filenamecom, ".com");
			strcat(fileNamecod, ".cod");
			//------------------Huffman Tree------------------//
			char temporaryCharacter1, temporaryCharacter2;
			int temporaryFrequency1, temporaryFrequency2;
			TreeNode* tmp1 = NULL;
			TreeNode* tmp2 = NULL;
			TreeNode* tmp = NULL;
			char characterCode[1000] = "", character;
			FILE* f;
			char* p = characterCode;
			char* q = characterCode;
			if (Frequency_Table->next == NULL) {
				characterCode[0] = '0';
				characterCode[1] = '\0';
				printf("%c:%s", Frequency_Table->tree.data.c, characterCode);
				FILE* f2 = fopen(fileNamecod, "w");
				if (f2 == NULL) {
					printf("Failed to open .cod file");
					return 1;
				}
				if (Frequency_Table->tree.data.c == '0' || Frequency_Table->tree.data.c == '1')
					fprintf(f2, "%d%s", Frequency_Table->tree.data.c, characterCode);
				else
					fprintf(f2, "%c%s", Frequency_Table->tree.data.c, characterCode);
				fclose(f2);
			}
			else {
				while (Frequency_Table->next->next != NULL) {
					tmp1 = (TreeNode*)malloc(sizeof(TreeNode));
					tmp2 = (TreeNode*)malloc(sizeof(TreeNode));
					tmp1->left = Frequency_Table->tree.left;
					tmp1->right = Frequency_Table->tree.right;
					if (tmp1->left)
						tmp1->left->Parent = tmp1;
					if (tmp1->right)

						tmp1->right->Parent = tmp1;


					Frequency_Table = removeFirst(Frequency_Table, &temporaryCharacter1, &temporaryFrequency1);
					tmp2->left = Frequency_Table->tree.left;
					tmp2->right = Frequency_Table->tree.right;

					if (tmp2->left)
						tmp2->left->Parent = tmp2;
					if (tmp2->right)
						tmp2->right->Parent = tmp2;

					Frequency_Table = removeFirst(Frequency_Table, &temporaryCharacter2, &temporaryFrequency2);
					tmp1->data.c = temporaryCharacter1;
					tmp1->data.freq = temporaryFrequency1;
					tmp2->data.freq = temporaryFrequency2;
					tmp2->data.c = temporaryCharacter2;
					Insert_Ascending2(Frequency_Table, tmp1, tmp2);
				}
				TreeNode root;
				root.data.c = '^';
				root.data.freq = Frequency_Table->tree.data.freq + Frequency_Table->next->tree.data.freq;
				root.left = &Frequency_Table->tree;
				root.left->Parent = &root;
				root.right = &Frequency_Table->next->tree;
				root.right->Parent = &root;
				root.Parent = NULL;
				//-----------------------------Huffman Code-----------------------------//
				code(&root, p, q, fileNamecod);
			}
			//-----------------------------compressing-----------------------------//
			char binarynum[8] = { '3','3','3','3','3','3','3','3' };
			int k = 0;
			int cnt = 0;
			int c = 0;
			decimalnum* decinum = NULL;
			char* compressed;
			int n = 0;
			char* input;
			char* cod;
			struct stat gg;
			int s = 0;
			char newline[10000];
			FILE* l;
			l = fopen(File_Destenation, "r");
			input = (char*)malloc(sizeof(char) * ss.st_size);
			fgets(input, ss.st_size + 1, l);
			for (int i = 0; i < ss.st_size; i++)
			{
				if (input[i] == '\n')
				{
					fgets(newline, ss.st_size + 1 - s, l);
					strcat(input, newline);
				}
				s++;
			}
			int inputsize = strlen(input);
			fclose(l);
			s = 0;
			FILE* o;
			o = fopen(fileNamecod, "r");
			stat(fileNamecod, &gg);
			cod = (char*)malloc(sizeof(char) * gg.st_size);
			fgets(cod, gg.st_size + 1, o);
			for (int i = 0; i < gg.st_size; i++)
			{
				if (cod[i] == '\n')
				{
					fgets(newline, gg.st_size + 1 - s, l);
					strcat(cod, newline);
				}
				s++;
			}
			int codsize = strlen(cod);
			fclose(o);
			for (int i = 0; i < inputsize; i++)
			{
				for (int j = 0; j < codsize; j++)
				{
					if (cod[j] == '4')
					{
						if (cod[j + 1] == '8')
						{
							if (input[i] == 48)
							{
								while (cod[j + 2] == 48 || cod[j + 2] == 49)
								{
									binarynum[k] = cod[j + 2];
									k++;
									if (k == 8)
									{
										binarytodecimal(binarynum, &decinum, &c);
										k = 0;
										binarynum[0] = { '3' };
										binarynum[1] = { '3' };
										binarynum[2] = { '3' };
										binarynum[3] = { '3' };
										binarynum[4] = { '3' };
										binarynum[5] = { '3' };
										binarynum[6] = { '3' };
										binarynum[7] = { '3' };
									}
									j++;
								}
							}
						}
						if (cod[j + 1] == '9')
						{
							if (input[i] == 49)
							{
								while (cod[j + 2] == 48 || cod[j + 2] == 49)
								{
									binarynum[k] = cod[j + 2];
									k++;
									if (k == 8)
									{
										binarytodecimal(binarynum, &decinum, &c);
										k = 0;
										binarynum[0] = { '3' };
										binarynum[1] = { '3' };
										binarynum[2] = { '3' };
										binarynum[3] = { '3' };
										binarynum[4] = { '3' };
										binarynum[5] = { '3' };
										binarynum[6] = { '3' };
										binarynum[7] = { '3' };
									}
									j++;
								}
							}
						}
					}
					if ((input[i] == cod[j]) && (input[i] != 48) && (input[i] != 49) && cod[j-1]!='4')
					{
						while (cod[j + 1] == 48 || cod[j + 1] == 49)
						{
							binarynum[k] = cod[j + 1];
							k++;
							if (k == 8)
							{
								binarytodecimal(binarynum, &decinum, &c);
								k = 0;
								binarynum[0] = { '3' };
								binarynum[1] = { '3' };
								binarynum[2] = { '3' };
								binarynum[3] = { '3' };
								binarynum[4] = { '3' };
								binarynum[5] = { '3' };
								binarynum[6] = { '3' };
								binarynum[7] = { '3' };
							}
							j++;
						}
					}
					if ((input[i + 1] == '\0') && (cod[j + 1] == '\0'))
					{
						for (int s = 0; s < 8; s++)
						{
							if (binarynum[s] == '3')
							{
								while ((binarynum[7] == '3') && (binarynum[0] != '3'))
								{
									for (int v = 7; v > 0; v--)
									{
										binarynum[v] = binarynum[v - 1];
									}
									cnt++;
								}
								for (int p = 0; p < cnt; p++)
								{
									binarynum[p] = '0';
								}
								binarytodecimal(binarynum, &decinum, &c);
								break;
							}
						}
					}
				}
			}
			compressed = (char*)malloc(sizeof(char) * c);
			decimalnum* t = decinum;
			for (int x = 0; x < c; x++)
			{
				compressed[x] = t->data;
				if (t->next == NULL)
				{
					break;
				}
				t = t->next;
			}
			FILE* e;
			e = fopen(filenamecom, "a");
			fprintf(e, "%d", cnt);
			fwrite(compressed, sizeof(char), c, e);
			fclose(e);
			printf("\nFile was compressed successfully\n");
		}
		if (choice == 2) {
			char fileNamecod[1000] = "";
			char filenamecom[1000] = "";
			strcat(fileNamecod, File_Destenation);
			int size = strlen(File_Destenation);
			char* file = &fileNamecod[size];
			for (int i = size; *file != '.'; i--, file--) {
				*file = '\0';
			}
			*file = '\0';
			strcpy(filenamecom, fileNamecod);
			strcat(filenamecom, ".com");
			strcat(fileNamecod, ".cod");
			FILE* L;
			char p[10000];
			struct stat ll;
			int s = 0;
			L = fopen(fileNamecod, "r");
			stat(fileNamecod, &ll);
			char* input;
			input = (char*)malloc(sizeof(char) * ll.st_size);
			fgets(input, ll.st_size + 1, L);
			for (int i = 0; i < ll.st_size; i++)
			{
				if (input[i] == '\n')
				{
					fgets(p, ll.st_size + 1 - s, L);
					strcat(input, p);
				}
				s++;
			}
			int inputsize = strlen(input);
			fclose(L);
			int extraBits;
			char* x;
			;
			int q = 0;
			char o[10000];
			int m;
			char B[2];
			FILE* l;
			l = fopen(filenamecom, "r");
			struct stat bb;
			stat(filenamecom, &bb);
			fgets(B, 2, l);
			x = (char*)malloc((sizeof(char)) * (bb.st_size));
			fgets(x, bb.st_size, l);
			for (int i = 0; i < bb.st_size; i++)
			{
				if (x[i] == '\n')
				{
					fgets(o, bb.st_size + 1 - q, l);
					strcat(x, o);
				}
				q++;
			}
			fclose(l);
			extraBits = atoi(B);
			int num_counter = strlen(x);
			char* binary;
			binary = (char*)malloc((sizeof(char)) * num_counter * 4);
			strcpy(binary, "");
			convertbin(x, binary);
			int num = strlen(binary);
			for (int j = 0; j < 8 - extraBits; j++) {
				binary[(num - 8) + j] = binary[(num - 8) + j + extraBits];
			}
			binary[(num - 8) + 8 - extraBits] = 0;
			char z[10000] = "";
			decode(binary, input, z);
			FILE* WW;
			WW = fopen("decomp.txt", "w");
			if (WW == NULL)
			{
				printf("Error");
				return 0;;
			}
			fprintf(WW, "%s", z);
			fclose(WW);
			printf("\nThe file has been extracted successfully saved as decomp.txt.\n");
		}
		if (choice == 3)
		{
			break;
		}
		if (choice != 1 && choice != 2 && choice != 3)
		{
			printf("\nINVALID INPUT !!!\n");
		}
		printf("\nPlease Choose :-  \n 1- Compress ( Enter 1 ) \n 2- Extract ( Enter 2 ) \n 3- End (Enter 3) \n");
		scanf("%d", &choice);
	} 	while (choice != 1 || choice != 2 || choice != 3);
	free(File_Destenation);
	return 0;
}