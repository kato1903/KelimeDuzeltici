#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * openfile(char*,char*);
int mergefile(FILE*,FILE*);
int testf(char* kelime,FILE* fp,int istek,FILE * out);
int strcicmp(char const *a, char const *b);
int main(){
	int i=0;
	int u;
	FILE* Kilavuz;
	FILE* dosyalar[30];
	FILE* textFile;
	FILE* output;
	output = fopen("output.txt","w");
	textFile = fopen("textFile.txt","r");
	Kilavuz = fopen("Kilavuz.txt","w+");

		for(i=0;i<26;i++){
			char d[20]="i.txt";
			d[0] = i+65;
			dosyalar[i]=openfile(d,"r");	// X acilamadi hatas� var W oldu�u i�in X te olabilir
		}									// diye silmedim
		dosyalar[26]=openfile("�.txt","r");
		dosyalar[27]=openfile("�.txt","r");
		dosyalar[28]=openfile("�.txt","r");
		dosyalar[29]=openfile("�.txt","r");
		for(i=0;i<30;i++){
			mergefile(Kilavuz,dosyalar[i]);
		}
		char kelime[100];
		int istek;
		printf("Letter Distance for correcting wrong written words: (1,2,3)");
		scanf("%d",&istek);
		while(!feof(textFile)){
		fgets(kelime,100,textFile);
		u = strlen(kelime);
		int p = 2;
		if(kelime[u-1]==10)     // yaz�lan kelimeden sonra alt sat�ra ge�mesin diye
		kelime[u-1]='\0';   
		while(kelime[u-p]==32){	// sizin payla�t���n�z textFile dosyas�nda ilk 2 kelimeden sonra
		kelime[u-p]='\0';       // bo�luk vard�. strlen o 2 kelime i�in di�erlerinden bir fazla
		kelime[u-p+1]='\0';     // g�steriyordu. Bu while kelimenin sonunda bo�luk varsa onu g�rmez
		p++;					// den gelmek i�in
	}
		
		fprintf(output,"%s ",kelime);
		testf(kelime,Kilavuz,istek,output);
		}
		
	fclose(output);
	fclose(textFile);
	fclose(Kilavuz);
	for(i=0;i<30;i++){
		fclose(dosyalar[i]);
	}
	return 0;
}
FILE * openfile(char a[20],char b[4]){
	FILE *fp;
	fp = fopen(a,b);
	if(fp==NULL)
	printf("Dosya Acilamadi %s \n",a);
	else{
		printf("Dosya Acildi %s \n",a);
	}
	return fp;
}
int mergefile(FILE*A,FILE*B){
	char kel[100];
    while(fgets(kel,100,B) != NULL)
	{	
		fputs(kel,A);
	}
    
}
int strcicmp(char const *a, char const *b)  // Bu fonksiyonu internetten ald�m hocam 
{                                           // strcmp nin buyuk kucuk fark etmeyeni
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}
int testf(char* kelime,FILE* fp,int istek,FILE* out){
//	printf("%s Fonksiyona Girildi",kelime);
	char kel[100];
	char dizi[1000][1000];  // textfiledeki 3 harfli olan T�rk�ede olmayan kelimelerin s��mas� i�in 
	strcpy(dizi[0]," -");   // bu kadar buyuk
	int i,j,k,u,s,forwhile;
	for(i=1;i<1000;i++){
		strcpy(dizi[i],"\n");
	}
	
	forwhile = 0;
	j=1;
	rewind(fp);
//	printf("%s While onu",kelime);
	while(  !feof(fp)  &&  (forwhile==0)    ){
	//	printf("%s While ici\n",kelime);
		fgets(kel,100,fp);
		u = strlen(kel);
		kel[u-1]='\0';
		
		if(strlen(kel)==strlen(kelime)){       // harf say�lar� e�itse i�lemler yap�l�yor
		
		
		s = 0;
		for(i=0;i<u;i++){                      // ka� harf ortak
			if(kelime[i]==kel[i]){
				s++;
			}
		}
		if( !strcicmp(kel,kelime) ){
			forwhile++;               // var olan kelimeyi bulduktan sonra whileden ��ks�n diye
			fprintf(out,"+");
		}
		else{                       // benzeyen kelimeleri diziye att�m ��nk� mesela k�lavuzda
			if(s + istek > strlen(kel) ){ // olan bir kelimeyi bulmadan �nce bulduklar�n� fonksiyona
				strcpy(dizi[j],kel);      // yazmas�n diye  
				j++;
			}
		}
	}
//	printf("%s While sonu",kelime);
}
if(forwhile==0)               // kelime k�lavuzda yoksa budu�u benzeyen kelimeleri fonksiyona yaz�yor
for(i=0;i<j;i++)
fprintf(out,"%s   ",dizi[i]);
fprintf(out,"\n\n");
// printf(" Fonksiyondan Cikiliyor\n");
}
