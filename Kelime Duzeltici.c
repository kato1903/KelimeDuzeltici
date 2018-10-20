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
			dosyalar[i]=openfile(d,"r");	// X acilamadi hatasý var W olduðu için X te olabilir
		}									// diye silmedim
		dosyalar[26]=openfile("Ç.txt","r");
		dosyalar[27]=openfile("Ý.txt","r");
		dosyalar[28]=openfile("Ö.txt","r");
		dosyalar[29]=openfile("Ü.txt","r");
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
		if(kelime[u-1]==10)     // yazýlan kelimeden sonra alt satýra geçmesin diye
		kelime[u-1]='\0';   
		while(kelime[u-p]==32){	// sizin paylaþtýðýnýz textFile dosyasýnda ilk 2 kelimeden sonra
		kelime[u-p]='\0';       // boþluk vardý. strlen o 2 kelime için diðerlerinden bir fazla
		kelime[u-p+1]='\0';     // gösteriyordu. Bu while kelimenin sonunda boþluk varsa onu görmez
		p++;					// den gelmek için
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
int strcicmp(char const *a, char const *b)  // Bu fonksiyonu internetten aldým hocam 
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
	char dizi[1000][1000];  // textfiledeki 3 harfli olan Türkçede olmayan kelimelerin sýðmasý için 
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
		
		if(strlen(kel)==strlen(kelime)){       // harf sayýlarý eþitse iþlemler yapýlýyor
		
		
		s = 0;
		for(i=0;i<u;i++){                      // kaç harf ortak
			if(kelime[i]==kel[i]){
				s++;
			}
		}
		if( !strcicmp(kel,kelime) ){
			forwhile++;               // var olan kelimeyi bulduktan sonra whileden çýksýn diye
			fprintf(out,"+");
		}
		else{                       // benzeyen kelimeleri diziye attým çünkü mesela kýlavuzda
			if(s + istek > strlen(kel) ){ // olan bir kelimeyi bulmadan önce bulduklarýný fonksiyona
				strcpy(dizi[j],kel);      // yazmasýn diye  
				j++;
			}
		}
	}
//	printf("%s While sonu",kelime);
}
if(forwhile==0)               // kelime kýlavuzda yoksa buduðu benzeyen kelimeleri fonksiyona yazýyor
for(i=0;i<j;i++)
fprintf(out,"%s   ",dizi[i]);
fprintf(out,"\n\n");
// printf(" Fonksiyondan Cikiliyor\n");
}
