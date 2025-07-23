#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	char buf[100];
	buf[0]='\0';
	if((start<0)|(end>s.codepoints)|(start>end)){
		return new_ustr(buf);
	}	
	int i=0,ibuf=0, icode=0;
	char t;
	while(!(ibuf>=end)){
		t=s.contents[i];
		if(utf8_codepoint_size(t)==1){
			if(icode>=start){
			//printf("size 1\n");
			buf[ibuf]=t;
			ibuf++;}
			i++;
			icode++;
		}
		else if(utf8_codepoint_size(t)==2){
			if(icode>=start){
			//printf("size 2\n");
			buf[ibuf]=t;
			buf[ibuf+1]=s.contents[i+1];
			//printf("rest of string: %s\n", &buf[ibuf]);
                        ibuf+=2;}
                        i+=2;
			icode++;
		}
		else if(utf8_codepoint_size(t)==3){
			if(icode>=start){
			//printf("size 3\n");
			buf[ibuf]=t;
                        buf[ibuf+1]=s.contents[i+1];
                        buf[ibuf+2]=s.contents[i+2];
			ibuf+=3;}
                        i+=3;
			icode++;
		}	
		else if(utf8_codepoint_size(t)==4){
			if(icode>=start){
			//printf("size 4\n");
			buf[ibuf]=t;
                        buf[ibuf+1]=s.contents[i+1];
                        buf[ibuf+2]=s.contents[i+2];
                        buf[ibuf+3]=s.contents[i+3];
			ibuf+=4;}
                        i+=4;
			icode++;
		}
		else if(utf8_codepoint_size(t)==-1){
			printf("something went wrong\n");
			break;
		}
	}
	buf[ibuf]='\0';
	return new_ustr(buf);
}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this

}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this

}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this

}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

