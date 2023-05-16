#include <stdio.h>
#include <stdlib.h>

typedef struct chr_ll_f_f{
	int chr_val;
	int chr_pos;
	struct chr_ll_f_f* next;
	struct chr_ll_f_f* prev;
} crl_t;

crl_t* frst_chr = NULL;

int curr_char_all = 0;
int max_char_all = 57;

// Sorts the binary text and prints it to the console for human readable format.
void gran_sort();
// Char mem allocation, needed for the besst possible way to make a str.
void chr_all_mem();

// Gets the char
int search_chr();
// Gets the char pos
int search_pos();

// Makes the file to read
void crt_grtst_file();

void main() {

	frst_chr = malloc(sizeof(crl_t));
	if(frst_chr != NULL) 
	{
		frst_chr->chr_val = 65;
		frst_chr->chr_pos = 0;
		chr_all_mem(frst_chr);
	}
	FILE *fp_c;
	fp_c = fopen("text.bin","rb");
	// If file don't exist then gen 1 from txt
	//if( fp_c == NULL) crt_grtst_file();
	crt_grtst_file();
	gran_sort();

}

void gran_sort() {
	int max_nl_inf = 0;
	FILE *fp_b;
	// Open the file
	fp_b = fopen("text.bin","rb");
	if( fp_b == NULL) {
		printf("No 'text.bin' file found, program terminated.");
		exit(1);
	}

	// Check the max char size.
	fseek(fp_b,0,SEEK_SET);
	fread(&max_nl_inf,sizeof(int),1,fp_b);
	int tmp_chr;
	int out_str[max_nl_inf][100];
	for (int isf = 0; isf < max_nl_inf; isf++) {
		// Max 100 chrs / line
		for (int zua = 0; zua < 100; zua++) {
			out_str[isf][zua] = 0;
		}
	}
	short is_div = 0;

	// Start to read the chars
	fseek(fp_b,sizeof(int),SEEK_CUR);
	
	// Needs to be 0 so it dosn't mess up the char position later
	char dividr = 0;
	char nl_l = search_chr(frst_chr, 29);
	int tmp_chr_val = 0;
	int tmp_ln = 0;
	int tmp_from_zero = 0;
	int tmp_nl_pos[max_nl_inf];
	int line_offst;
	short frst_chk = 0;
	int tmp_cntr = 0;

	// Read the binary and get the chars from LL
	while(fread(&tmp_chr,sizeof(int),1,fp_b) == 1) {
		line_offst = 0;
		// Check if its a char divider (0)
		if( tmp_chr == dividr ) is_div = 1;

		// Increment the char position
		if ( is_div == 1) {
			tmp_cntr++;
		}

		// Check if char divider
		if( tmp_chr != dividr ){
			// Get the chararcter from char position
			char t_c = search_chr(frst_chr, tmp_cntr);
			
			// Go thru the first time to get the linebreaks
			if (t_c == nl_l && frst_chk == 0) {
				// If the max linebreak is reached rewind the file and set the char position to 0
				if(tmp_ln == max_nl_inf-1 ) {
					tmp_cntr = 0;
					fseek(fp_b,2*sizeof(int),SEEK_SET); 
					frst_chk = 1;
				}
				// Set the linebreak positions in the linebreak position array
				tmp_nl_pos[tmp_ln++] = tmp_chr;
				continue;
			}

			// Check if the character is in witch row
			for (int ksa = 0; ksa < max_nl_inf; ksa++) {
				if( (tmp_chr - tmp_nl_pos[ksa]) < 0) {
					line_offst = ksa;
					break;
				}
			}
			// If not the first check for the linebreaks 
			if ( frst_chk  != 0 ) {
				// Skip the below code if linebreak
				if (t_c == nl_l) continue;
				
				// Check the position relative to the row start
				int line_pos = (tmp_chr < tmp_nl_pos[0]) ? tmp_chr-1 : (tmp_chr-tmp_nl_pos[line_offst-1] -2);
				
				// Save the character to the desired position
				out_str[line_offst][line_pos] = t_c;
				
			}
		}

		// Reset the divider checker
		is_div = 0;
	
	}

	fclose(fp_b);
	
	// Print out the characters.
	for(int az = 0; az < max_nl_inf; az++) {
		for(int ak = 0; ak < 100; ak++)
		{
			if(out_str[az][ak] != 0)
			printf("%c",out_str[az][ak]);
			

		}
		printf("\n");
	}

};

// Search the position for the char in the LL
int search_pos(crl_t * head, int n_val) {
    crl_t* curr = head;
	int r_pos = 500;
    while (curr != NULL) {
		if(curr->chr_val == n_val) {
			r_pos = curr->chr_pos;
		}
        curr = curr->next;
    }
	return r_pos;
}

// Search the character from position in the LL
int search_chr(crl_t * head, int n_pos) {
    crl_t* curr = head;
	int r_chr = 0;
    while (curr != NULL) {
		if(curr->chr_pos == n_pos) {
			r_chr = curr->chr_val;
		}
        curr = curr->next;
    }
	return r_chr;
}


// Generate the default "character set" recursively

void chr_all_mem(crl_t* prev_chr) {
	// Previous character pointer
	crl_t* curr = prev_chr;

	if (curr_char_all < max_char_all) {	
		
			curr_char_all++;
		
			curr->next = malloc(sizeof(crl_t));
			curr->next->chr_val = curr->chr_val + 1;
			curr->next->chr_pos = curr_char_all;
		
			if(curr->next != NULL) {
		
				chr_all_mem(curr->next);
		
			}
	}
	else if (curr_char_all == max_char_all)
	{
		curr->next = malloc(sizeof(crl_t));
		curr->next->chr_val = 32;
		curr->next->chr_pos = curr_char_all+1;
	}
	
	else {
		curr->next = NULL;
		return;
	}
}


void crt_grtst_file() {
	char tmp_char[100];
	int max_size = max_char_all + 2;
	int  all_pos_char_cnt[max_size][2];

	for (int z = 0; z < max_size; z++) {
		// Size of the dyn arr
		all_pos_char_cnt[z][0] = 0;
		// Position in the dyn arr
		all_pos_char_cnt[z][1] = 0;

	}

	int  *all_pos_char[max_size];

	FILE *fp;
	fp = fopen("text.txt","r");
	if (fp == NULL){
		printf("Couldn't open 'text.txt' please check if it exists!\n");
		exit(1);
	}
	// Read by line
	while(fgets(tmp_char,100,fp)) {
		// Parse each chr
		for(int i = 0; i < 100; i++) {
			// Check the chr position and incr the number
			all_pos_char_cnt[search_pos(frst_chr,tmp_char[i])][0]++;
			// If EOL increment the 29th element counter and break
			if(tmp_char[i] == 10) {
				all_pos_char_cnt[29][0]++;
				break;
			}
			//printf("%c | %d \n",tmp_char[i],tmp_char[i]);
		}
	}
	
	// Allocatte dynamic arrays given the max count for each char
	for (int zy = 0; zy < max_size; zy++) {
		all_pos_char[zy] = malloc(all_pos_char_cnt[zy][0] * sizeof(int));
	}


	
	
	// Position in file
	int tmp_cntr = 0;
	int max_nl_cntr = 0;
	// Rewind the file pointer to the start
	if(fseek(fp,0,SEEK_SET) == 0 && fp != NULL) {
		while(fgets(tmp_char,100,fp)) {
			for(int iz = 0; iz < 100; iz++) {

				// Check if new line if yes the 29th char in the LL is the linebreak in the binary file
				if(tmp_char[iz] == 10) {
					max_nl_cntr++;
					all_pos_char[29][all_pos_char_cnt[29][1]++] = tmp_cntr++;
					break;
				}

				// Get the position in the LL for the chr
				int chr_pos_in = search_pos(frst_chr,tmp_char[iz]);

				// Write the position for the char from the txt
				if(all_pos_char[chr_pos_in] != NULL) {
					all_pos_char[chr_pos_in][all_pos_char_cnt[chr_pos_in][1]++] = 1 + tmp_cntr++;
				}
				else {
					printf("%c | %d \n",tmp_char[iz],tmp_char[iz]);
					printf("No mem\n");
				}				
			}
		}
	}
	
	fclose(fp);

	// Set a divider
	int chr_divider = 0;

	fp = fopen("text.bin","wb");

	// Write to the binary file.
	fwrite(&max_nl_cntr,sizeof(int),1,fp);

	fwrite(&chr_divider,sizeof(int),1,fp);


	for (int xy = 0; xy < max_size; xy++) {
		for (int zs = 0; zs < all_pos_char_cnt[xy][0]; zs++) {
			fwrite(&all_pos_char[xy][zs],sizeof(int),1,fp);
			
		}
		// Free up the dyn arrays.
		free(all_pos_char[xy]);
		fwrite(&chr_divider,sizeof(int),1,fp);
	}
	fclose(fp);


}