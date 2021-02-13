#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_k
{
    int k;
    struct node_k* komsular;
};
struct node
{
    int no;
    char ad[15];
    char bolge[3];
    int k_sayisi;
    struct node* onceki;
    struct node* sonraki;
    struct node_k* komsular;
};

struct node_k* tara_k = NULL;
struct node_k* start_k = NULL;
struct node_k* tmp_k;

struct node* tara = NULL;
struct node* start = NULL;
struct node* tmp_s;
struct node* tmp_o;

int main()
{
    int n,m;
    char bolge[3];
    char ad[15];
    FILE *dosya = fopen("sehirler.txt","r");



    char gecici_satir[1000];                                /// gecici satir kaydi
    int satir_sayisi=0;                                    /// satir sayisini sayar
    while ( fgets(gecici_satir, 1000, dosya) != NULL )      /// satir sayiyisi bul
    {
        satir_sayisi++;                                    /// her satirda degeri 1 arttir
    }
    char satirlar[satir_sayisi][1000];                     /// satirlari tutan iki boyutlu dizinin satir boyutunu ver(satirlar[satir_sayisi][])

    fclose(dosya);                                         /// acik olan dosyayi kapatir
    dosya=fopen("sehirler.txt","r");                           /// dosyayi tekrar acar (bu iki islem en basa dönmesi icin)
    int i=0,j;
    int satir_sonlari[100];
    satir_sayisi=0;
    while ( fgets(gecici_satir, 1000, dosya) != NULL )      /// satirlara ata
    {
        strcpy(satirlar[satir_sayisi],gecici_satir);
        satir_sonlari[satir_sayisi]=strlen(satirlar[satir_sayisi]);
        satir_sayisi++;
    }
    i=0;
    /*while(i<satir_sayisi)
    {
        printf("%s",satirlar[i]);
        i++;
    }*/
    printf("\nsatir_sayisi = %d\n",satir_sayisi);
    parcala_ata(satirlar,satir_sayisi,satir_sonlari);
    parcala_komsu(satirlar,satir_sayisi,satir_sonlari);
    yazdir();

    while(1)
    {
        int kontrol = 1;
        printf("\n\n1- Belirli sayidan fazla komsuya sahip sehirler\n"
               "2- Belirli bolgedeki sehirler\n"
               "3- Belirli sehrin bilgileri ve komsularinin bilgileri\n"
               "4- Sehir Ekleme\n"
               "5- Sehir silme\n"
               "6- Belirli aralikta komsu sayisi ve ozel komsulugu olan sehirler\n"
               "7- Ekrana yaz\n"
               "8- cik ve dosyaya yaz\n"
               "Secim yapiniz: ");
        scanf("%d",&n);
    switch(n)
    {
        case 1:
        printf("girdiginiz sayiya esit ve daha fazla komsu sayisi olan sehirler yazdirilacaktir.\nSayi giriniz: ");
        scanf("%d",&n);
        Komsu_Sayisi(n);
        break;

        case 2:
        printf("Hangi bolgedeki sehirler yazilsin? (AK,GA,EG,DA,KA,IA,MA): ");
        scanf("%s",bolge);
        Bolgedeki_Sehirler(bolge);
        break;

        case 3:
        while(1)
        {
            printf("Sehri;\n 1-Isim ile arayacaksaniz\n 2-Plaka ile arayacaksaniz\n : ");
            scanf("%d",&n);
            if(n==1)
            {
                printf("Sehrin ismini giriniz: ");
                scanf("%s",&ad);
                Sehir_komsu_bilgileri_1(ad);
                break;
            }
            if(n==2)
            {
                printf("Sehrin plaka kodunu girin: ");
                scanf("%d",&n);
                Sehir_komsu_bilgileri_2(n);
                break;
            }
        }
        break;

        case 4:
        while(1)
        {
            printf("Eklenecek sehrin sirayla plaka kodunu, adini ve bulundugu bolgeyi girin\n: ");
            scanf("%d %s %s",&n,&ad,&bolge);
            if((plaka_dugum(n)) != -1)
                {
                    printf("Plaka baska bir sehre ait\n");
                    continue;
                }
            if(No_ara(ad) != -1)
                {
                    printf("Ad baska bir sehre ait\n");
                    continue;
                }
            break;
        }
        sehir_ekle(n,ad,bolge);
        break;

        case 5:
        while(1)
        {
            printf("\nSilinecek sehrin plaka kodunu girin\n: ");
            scanf("%d",&n);
            if(plaka_dugum(n) == -1)
            {
                printf("Olmayan sehri silemezsiniz.\n");
                continue;
            }
            break;
        }
        sehir_sil(n);
        break;

        case 6:
        printf("Komsu araligi sayisi giriniz");
        scanf("%d %d",&n,&m);
        bonus(n,m);
        break;

        case 7:
        yazdir();
        break;

        case 8:
            kontrol = -1;

        default:
            printf("Gecersiz Secim");
        break;
    }
        if(kontrol == -1 )
            break;
    }

    yazdir_cikti();



}

void parcala_ata(char satirlar [][1000],int satir_sayisi,int satir_sonlari[])
{
    for(int i=0; i<satir_sayisi; i++)
    {
        int komsu_sayisi=0;
        int no,konum=0,temp=0;
        char *ayrac=",\n",ad[15],bolge[3];
        while(1)
        {
            char *kelime=strtok(&satirlar[i][temp],ayrac);
            temp+=strlen(kelime)+1;
            konum++;
            if(konum==1)
                no = atoi(kelime);
            if(konum==2)
                strcpy(ad,kelime);
            if(konum==3)
                strcpy(bolge,kelime);
            //printf("%s ",kelime);
            if(temp>=satir_sonlari[i])
                break;
        }
        konum-=3;
        //printf("%d\n\n",konum);
        sona_ekle(no,konum,ad,bolge);
    }
}

void sona_ekle(int plaka,int komsu_sayisi,char sehir[],char blg[])
{
    struct node* sona_eklenecek = (struct node*)malloc(sizeof(struct node));
    sona_eklenecek->onceki == NULL;
    if(start == NULL)
        start = sona_eklenecek;
    else
    {
        tara = start;
        while(tara->sonraki!=NULL)
            tara=tara->sonraki;
        tara->sonraki = sona_eklenecek;
        sona_eklenecek->onceki = tara;
    }

    strcpy(sona_eklenecek->bolge,blg);
    strcpy(sona_eklenecek->ad,sehir);
    sona_eklenecek->k_sayisi = komsu_sayisi;
    sona_eklenecek->no = plaka;
    sona_eklenecek->sonraki = NULL;
}

void parcala_komsu(char satirlar [][1000],int satir_sayisi,int satir_sonlari[])
{
    for(int i=0; i<satir_sayisi; i++)
    {
        int dizi[10],say=0,konum=0,temp=0,no;
        char *ayrac=",\n";
        while(1)
        {
            char *kelime=strtok(&satirlar[i][temp],ayrac);
            temp+=strlen(kelime)+1;
            if(konum == 0)
                no = atoi(kelime);
            if(konum>2)
            {
                dizi[say]=No_ara(kelime);
                say++;
            }
            if(temp>=satir_sonlari[i])
            {
                Komsu_Bagla(no,dizi,say);
                break;
            }
            konum++;
            //printf("%s ",kelime);
        }
        konum-=3;
        //printf("%d\n\n",konum);
        //sona_ekle(no,konum,ad);
    }
}

int No_ara(char *sehir)
{
    if(start == NULL)
        printf("dugum bos");
    else
    {
        tara = start;
        while(memcmp(tara->ad,sehir,sizeof(sehir))!=0)
        {
            //printf("%s",tara->ad);
            tara=tara->sonraki;
            if(tara == NULL)
                return -1;
        }
        //printf("%s %d\n\n",tara->ad,tara->no);
    }
    return tara->no;
}

void Komsu_Bagla (int plaka,int dizi[10],int boyut)
{
    sirala(dizi,boyut);
    struct node* k = plaka_dugum(plaka);

    for(int i=0; i<boyut; i++)
    {
        struct node_k* sona_eklenecek = (struct node_k*)malloc(sizeof(struct node_k));
        sona_eklenecek->k = dizi[i];
        sona_eklenecek->komsular = NULL;
        if(i==0)
        {
            k->komsular = sona_eklenecek;
            ///printf("%d  ",*k->komsular);
        }
        else
        {
            tara_k = k->komsular;

            while(tara_k->komsular!=NULL)
                tara_k=tara_k->komsular;

            tara_k->komsular = sona_eklenecek;
            ///printf("%d  ",*tara_k->komsular);
        }
    }
}

int plaka_dugum(int plaka)
{
    if(start == NULL)
        printf("dugum bos");
    else
    {
        tara = start;
        while(tara->no!=plaka)
        {
            //printf("%s",tara->ad);
            tara=tara->sonraki;
            if(tara == NULL)
                return -1;
        }
        //printf("\n\n%s %d\n",tara->ad,tara->no);
    }
    return tara;
}

void sirala(int dizi[],int boyut)
{
    int i,j,temp;
    for(i=0; i<boyut-1; i++)
    {
        for(j=0; j<boyut-1-i; j++)
        {
            if(dizi[j]>dizi[j+1])
            {
                temp=dizi[j];
                dizi[j]=dizi[j+1];
                dizi[j+1]=temp;
            }
        }
    }
}

void yazdir()
{
    if(start == NULL)
        printf("dugum bos");
    else
    {
        tara = start;
        while(tara->sonraki!=NULL)
        {
            printf("%-5d %-14s %3s %3d Komsular",tara->no,tara->ad,tara->bolge,tara->k_sayisi);
            if(tara->komsular == NULL)
                printf(" komsu yok\n        |^\n        v|\n");
            else
            {
                tara_k = tara->komsular;

                while(tara_k->komsular!=NULL)
                {
                    printf(" =>%3d",tara_k->k);
                    tara_k=tara_k->komsular;
                }
                printf(" =>%3d\n        |^\n        v|\n",tara_k->k);
            }
            //start_k = tara->komsular;
            //komus_yaz();
            tara=tara->sonraki;
        }
        printf("%-5d %-14s %3s %3d Komsular",tara->no,tara->ad,tara->bolge,tara->k_sayisi);
        if(tara->komsular == NULL)
            printf(" komsu yok\n");
        else
        {
            tara_k = tara->komsular;

            while(tara_k->komsular!=NULL)
            {
                printf(" =>%3d",tara_k->k);
                tara_k=tara_k->komsular;
            }
            printf(" =>%3d\n",tara_k->k);
        }
    }
}

void Komsu_Sayisi(int n)
{
    if(start == NULL)
        printf("dugum bos");
    else
    {
        tara = start;
        while(tara->sonraki!=NULL)
        {
            if(n<tara->k_sayisi)
                printf("%s\n",tara->ad);
            tara=tara->sonraki;
        }
        if(n<tara->k_sayisi)
            printf("%s\n",tara->ad);
    }
}

void Bolgedeki_Sehirler(char *blg)
{
    if(start == NULL)
        printf("dugum bos");
    else
    {
        tara = start;
        while(tara->sonraki!=NULL)
        {
            if(strstr(tara->bolge,blg) && strlen(blg) == 2)
                printf("%-5d %-14s %3d\n",tara->no,tara->ad,tara->k_sayisi);
            tara=tara->sonraki;
        }
        if(strstr(tara->bolge,blg) && strlen(blg) == 2)
            printf("%-5d %-14s %3d\n",tara->no,tara->ad,tara->k_sayisi);
    }
}

void Sehir_komsu_bilgileri_1(char *sehir)
{
    if(start == NULL)
        printf("dugum bos");
    else
    {
        tara = start;
        while(memcmp(tara->ad,sehir,sizeof(sehir))!=0)
        {
            //printf("%s",tara->ad);
            tara=tara->sonraki;
            if(tara==NULL)
            {
                printf("%s sehrini eklemek icin eklemeyi secin",sehir);
                return;
                ///yapilandirilacak
            }
        }
        printf("%s %3d %3s Komsu %3d\n\n",tara->ad,tara->no,tara->bolge,tara->k_sayisi);
        if(tara->komsular == NULL)
            printf("komsu yok");
        else
        {
            tara_k = tara->komsular;

            while(tara_k->komsular!=NULL)
            {
                //printf(" =>%3d",tara_k->k);
                komsu_bilgileri(tara_k->k);
                tara_k=tara_k->komsular;
            }
            komsu_bilgileri(tara_k->k);
            //printf(" =>%3d\n        |^\n        v|\n",tara_k->k);
        }
    }
}

void Sehir_komsu_bilgileri_2(int plaka)
{
    if(start == NULL)
        printf("dugum bos");
    else
    {
        tara = start;
        while(plaka!=tara->no)
        {
            //printf("%s",tara->ad);
            tara=tara->sonraki;
            if(tara==NULL)
            {
                printf("%d plakali sahir yok, eklemek icin eklemeyi secin");
                return;
                ///yapilandirilacak
            }
        }
        printf("%s %3d %3s Komsu %3d\n\n",tara->ad,tara->no,tara->bolge,tara->k_sayisi);
        if(tara->komsular == NULL)
            printf("komsu yok");
        else
        {
            tara_k = tara->komsular;

            while(tara_k->komsular!=NULL)
            {
                //printf(" =>%3d",tara_k->k);
                komsu_bilgileri(tara_k->k);
                tara_k=tara_k->komsular;
            }
            komsu_bilgileri(tara_k->k);
            //printf(" =>%3d\n        |^\n        v|\n",tara_k->k);
        }
    }
}

void komsu_bilgileri(int plaka)
{
    if(start == NULL)
        printf("dugum bos");
    else
    {
        tara = start;
        while(tara->no!=plaka)
        {
            //printf("%s",tara->ad);
            tara=tara->sonraki;
        }
        //printf("\n\n%s %d\n",tara->ad,tara->no);
        printf("%-15s %3d %3s\n",tara->ad,tara->no,tara->bolge);

    }
    return tara;
}

void yazdir_cikti()
{
    FILE *cikti = fopen("cikti.txt","w");
    if(start == NULL)
        fprintf(cikti,"dugum bos");
    else
    {
        tara = start;
        while(tara->sonraki!=NULL)
        {
            fprintf(cikti,"%-5d %-14s %3s %3d Komsular",tara->no,tara->ad,tara->bolge,tara->k_sayisi);
            if(tara->komsular == NULL)
                fprintf(cikti," komsu yok\n        |^\n        v|\n");
            else
            {
                tara_k = tara->komsular;

                while(tara_k->komsular!=NULL)
                {
                    fprintf(cikti," =>%3d",tara_k->k);
                    tara_k=tara_k->komsular;
                }
                fprintf(cikti," =>%3d\n        |^\n        v|\n",tara_k->k);
            }
            //start_k = tara->komsular;
            //komus_yaz();
            tara=tara->sonraki;
        }
        fprintf(cikti,"%-5d %-14s %3s %3d Komsular",tara->no,tara->ad,tara->bolge,tara->k_sayisi);
        if(tara->komsular == NULL)
            fprintf(cikti,"dugum bos\n");
        else
        {
            tara_k = tara->komsular;

            while(tara_k->komsular!=NULL)
            {
                fprintf(cikti," =>%3d",tara_k->k);
                tara_k=tara_k->komsular;
            }
            fprintf(cikti," =>%3d\n",tara_k->k);
        }
    }
    fclose(cikti);
}






void sehir_ekle(int plaka,char sehir[],char blg[])
{
    struct node* eklenecek = (struct node*)malloc(sizeof(struct node));

    strcpy(eklenecek->ad,sehir);
    eklenecek->no = plaka;
    strcpy(eklenecek->bolge,blg);

    if(start == NULL)
    {
        printf("dugum bos !!");
        return;
    }
    else if(start->no > plaka)
    {
        eklenecek->onceki = NULL;
        start->onceki = eklenecek;
        eklenecek->sonraki = start;
        start = eklenecek;
    }
    else
    {
        tara = start;
        while(1)
        {
            if(tara->sonraki == NULL)
            {
                tara->sonraki= eklenecek;
                eklenecek->komsular = NULL;
                eklenecek->onceki = tara;
                break;
            }
            else if(tara->sonraki->no > plaka)
            {
                tmp_s = tara->sonraki;
                //tmp_o = tara->sonraki->onceki;
                tara->sonraki = eklenecek;
                //eklenecek->onceki = tmp_o;
                eklenecek->sonraki = tmp_s;
                break;
            }
            tara = tara->sonraki;

        }
    }
    int no,dizi[10],say=0;
    while(1)
    {
        printf("komsu plakasi giriniz, cikmak icin -1 gonderin\n: ");
        scanf("%d",&no);
        if(no==-1)
        {
            Komsu_Bagla(plaka,dizi,say);
            break;
        }
        if((plaka_dugum(no)) == -1 || plaka == no)
        {
            printf("Boyle bi plaka yok yada kendi ile komsu olamaz\n");
                    continue;
        }
        dizi[say] = no;
        say++;
        komsu_ekle(no,plaka);
        if(say>10)
        {
            printf("10 dan fazla komsu eklenemez!\n");
            say--;
            Komsu_Bagla(plaka,dizi,say);
            break;
        }
    }
    eklenecek->k_sayisi = say;
}
void komsu_ekle(int plaka, int veri)
{
    struct node* kom = plaka_dugum(plaka);
    struct node_k* eklenecek = (struct node_k*)malloc(sizeof(struct node_k));
    eklenecek->k = veri;
    if(kom->komsular == NULL)
    {
        kom->komsular = eklenecek;
        eklenecek->komsular = NULL;
    }
    else if(kom->komsular->k > veri)
    {
        tmp_k = kom->komsular;
        kom->komsular = eklenecek;
        eklenecek->komsular = tmp_k;
    }
    else
    {
        tara_k = kom->komsular;
        while(1)
        {
            if(tara_k->komsular == NULL)
            {
                tara_k->komsular = eklenecek;
                eklenecek->komsular = NULL;
                break;
            }
            else if(tara_k->komsular->k > veri)
            {
                tmp_k = tara_k->komsular;
                tara_k->komsular = eklenecek;
                eklenecek->komsular = tmp_k;
                break;
            }
            tara_k = tara_k->komsular;

        }

    }
    kom->k_sayisi++;
    //printf("%d,%d",kom->komsular->k,plaka);
}

void sehir_sil(int n)
{
    struct node* silinecek = plaka_dugum(n);
    if(start->no == n)
    {
        tmp_s = start->sonraki;
        ///
        free(start);
        tmp_s->onceki = NULL;
        start = tmp_s;
    }
    else if(silinecek->sonraki == NULL)
    {
        tmp_o = silinecek->onceki;
        ///
        free(silinecek);
        tmp_o->sonraki = NULL;
    }
    else
    {
        tmp_s = silinecek->sonraki;
        tmp_o = silinecek->onceki;
        ///
        free(silinecek);
        tmp_o->sonraki = tmp_s;
        tmp_s->onceki = tmp_o;
    }
    komsu_sil(n);
}
void komsu_sil(int n)
{
    //struct node* silinecek = plaka_dugum(n);
    if(start == NULL)
        printf("dugum bos\n");
    else
    {
        tara = start;
        while(tara->sonraki!=NULL)
        {
            //printf("%-5d %-14s %3s %3d Komsular",tara->no,tara->ad,tara->bolge,tara->k_sayisi);
            if(tara->komsular == NULL)
                printf(" komsu yok\n");
            else
            {
                tara_k = tara->komsular;
                int x=1;
                if(tara_k->k == n)
                {
                    tara->k_sayisi--;
                    tmp_k = tara_k;
                    tara->komsular = tara_k->komsular;
                    free(tmp_k);
                    x=0;
                }
                else
                    while(tara_k->komsular!=NULL)
                    {
                        if(tara_k->k == n)
                        {
                            tara->k_sayisi--;
                            tmp_k->komsular = tara_k->komsular;
                            free(tara_k);
                            x=0;
                            break;
                        }
                        ///printf(" =>%3d",tara_k->k);
                        tmp_k = tara_k;
                        tara_k=tara_k->komsular;
                    }
                if(tara_k->k ==n && x==1)
                {
                    tara->k_sayisi--;
                    tmp_k->komsular = NULL;
                    free(tara_k);
                }
                ///printf(" =>%3d\n        |^\n        v|\n",tara_k->k);
            }
            //start_k = tara->komsular;
            //komus_yaz();
            tara=tara->sonraki;
        }
        //printf("%-5d %-14s %3s %3d Komsular",tara->no,tara->ad,tara->bolge,tara->k_sayisi);
        if(tara->komsular == NULL)
            printf(" komsu yok\n");
        else
        {
            tara_k = tara->komsular;
            int x=1;
            if(tara_k->k == n)
            {
                tara->k_sayisi--;
                tmp_k = tara_k;
                tara->komsular = tara_k->komsular;
                free(tmp_k);
                x=0;
            }
            else
                while(tara_k->komsular!=NULL)
                {
                    if(tara_k->k == n)
                    {
                        tara->k_sayisi--;
                        tmp_k->komsular = tara_k->komsular;
                        free(tara_k);
                        x=0;
                        break;
                    }
                    ///printf(" =>%3d",tara_k->k);
                    tmp_k = tara_k;
                    tara_k=tara_k->komsular;
                }
            if(tara_k->k ==n && x==1)
            {
                tara->k_sayisi--;
                tmp_k->komsular = NULL;
                free(tara_k);
            }
            ///printf(" =>%3d\n        |^\n        v|\n",tara_k->k);
        }
    }
}

void bonus(int kucuk, int buyuk)
{
    if(kucuk>buyuk)
    {
        int temp = kucuk;
        kucuk = buyuk;
        buyuk = temp;
    }
    char kafa[15];
    int kafa_dizi[10],sayac=0;
    while(1)
    {
        printf("Komsu olan sehrin adini girin.\n(cikmak icin '-' eksi tuslayip gonderin)\n: ");
        scanf("%s",&kafa);
        if (kafa[0]=='-')
            break;
        kafa_dizi[sayac]=No_ara(kafa);
        sayac++;
    }
    sirala(kafa_dizi,sayac);

    if(start == NULL)
        printf("dugum bos");
    else
    {
        tara = start;
        while(tara->sonraki!=NULL)
        {
            int kont = 0;
            if(kucuk<tara->k_sayisi && buyuk>tara->k_sayisi)
            {
                for(int i=0; i<sayac;i++)
                {
                tara_k = tara->komsular;
                while(tara_k!=NULL)
                {

                    if(tara_k->k == kafa_dizi[i])
                        kont = 1;
                    tara_k = tara_k->komsular;
                }
                if(i == sayac-1 && kont == 1)
                {
                    printf("%s\n",tara->ad);
                }
                else if(kont == 1)
                {
                    kont = 0;
                    continue;
                }
                else
                    break;
                }
            }

            tara=tara->sonraki;
        }
        int kont=0;
        if(kucuk<tara->k_sayisi && buyuk>tara->k_sayisi)
        {
            for(int i=0; i<sayac;i++)
                {
                tara_k = tara->komsular;
                while(tara_k!=NULL)
                {

                    if(tara_k->k == kafa_dizi[i])
                        kont = 1;
                    tara_k = tara_k->komsular;
                }
                if(i == sayac-1 && kont == 1)
                {
                    printf("%s\n",tara->ad);
                }
                else if(kont == 1)
                {
                    kont = 0;
                    continue;
                }
                else
                    break;
                }
        }
    }
}





