#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h> 

int main()
{
	FILE *fin = fopen("test1.c", "r");
	FILE *fout = fopen("new.c", "w");
	int i = 0, slkol = 0; //slkol - количество слешей, идущих подряд 
	char cArray[10000], c = 'n', lc = 'n', s[10000], cc = 'n', ccc = 'n';
	int len = strlen(cArray);
	int kav1 = 0, kav2 = 0; // Кавычки. 1 - '_', 2 - "_"; 

	for (i = 0; i<10000; i++) { s[i] = cArray[i] = '\0'; }

	while (!feof(fin)) {
	xyz:
		c = fgetc(fin);
		if (feof(fin)) { break; }
		eto:
		//кавычки типа "_" 
		if (c == '\"') {
			fputc('\"', fout);
			i = 0;
			slkol = 0;
			lc = 'n';
			c = '#';
			while ((c != '\"') || (slkol % 2 != 0)) {
			repa:lc = c;
				c = fgetc(fin);
				if (feof(fin)) { goto tuda; }
				if (((c == '\n') && (lc == '\\') && (slkol % 2 == 1))) { fputc('\n', fout); slkol = 0; goto repa; }
				else { if (c == '\n') { fputc('\n', fout); goto xyz; } }
				if (c == '\\') {
					if (lc == '\"') { slkol = 1; }
					else { slkol++; }
				}
				else {
					if (c == '\"') {
						if (lc == '\"') {
							if (slkol % 2 == 1) {
								fputc(c, fout); goto xyz;
							}
							else { slkol = 0; }
						}
					}
					else { slkol = 0; }
				}
				fputc(c, fout);
			}
			//fputc('#', fout); 
			goto xyz;
		}
		else {
		uidi:;
			//TODO Уйти в кулинарный 
			//кавычки типа '_' 
			if (c == '\'') {
				fputc('\'', fout);
				i = 0;
				slkol = 0;
				lc = 'n';
				c = '#';
				while ((c != '\'') || (slkol % 2 != 0)) {
				repet:lc = c;
					c = fgetc(fin);
					if (feof(fin)) { goto tuda; }
					if (c == '\n') { fputc('\n', fout); goto xyz; }
					if (c == '\\') {
						if (lc == '\'') { slkol = 1; }
						else { slkol++; }
					}
					else {
						if (c == '\'') {
							if (lc == '\'') { if (slkol % 2 == 1) {
								fputc(c, fout); goto xyz;
							}
							else { slkol = 0; }
						}
						}
						else { slkol = 0; }
					}
					fputc(c, fout);
				}
				goto xyz;
			}
			else {
				//. 

				//Комментарии 
				if (c == '/') {
					c = fgetc(fin); if (feof(fin)) { fputc('/', fout); goto tuda; }
					if (c == '/') {
						fputc('\n', fout); while (1) {
							lc = c;
							c = fgetc(fin);
							if (feof(fin)) { goto tuda; }
							if (c == '\n') {
								if (lc == '\\') {
									continue;
								}
								else { break; }
							}
						}
						goto xyz;
					}
					else {
						if (c == '*') {
							cc = 'i'; ccc = 'i'; while ((cc != '*') || (ccc != '/')) { cc = ccc; ccc = fgetc(fin); if (feof(fin)) { goto tuda; } } goto xyz;
						}
						else {
							fputc('/', fout);  goto eto;
						}
					}
					goto xyz;
				}
				else { fputc(c, fout); }
			}
		}

		//----------------------Комментарии 

	}
tuda:
	fclose(fin);
	fclose(fout);
	printf("\nEnd.\n");
	return 0;
}