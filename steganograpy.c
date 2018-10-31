#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct BMPFILEHEADER
    {
        int height;
        int width;
        int imagesize;
        int bpp;
        char filetype[3];
    };
struct PIXEL
    {
        unsigned int red;
        unsigned int blue;
        unsigned int green;
    };


encrypt()
    {
        system("cls");
        struct PIXEL p;
        struct BMPFILEHEADER bmp;

        char fpath[100];
        char ch;
        char sec_msg[10000];

        printf("\t\t\t\t\t  **************************************\n");
        printf("\t\t\t\t\t\t\tENCRYPTION\n");
        printf("\t\t\t\t\t  **************************************\n\n");

        FILE *eimage;

        printf("Enter the path of the file:");
        scanf("%s",fpath);
        eimage=fopen(fpath,"rb+");

        bmp.filetype[0]=fgetc(eimage);
        bmp.filetype[1]=fgetc(eimage);
    if(!strcmp(bmp.filetype,"BM"))
    {
                bmp.imagesize=fgetw(eimage);


        fseek(eimage,100,SEEK_SET);
        while((ch = getc(eimage))!= EOF)
            {
                ch=ch>>1;
                ch=ch<<1;

                fseek(eimage,-1,SEEK_CUR);
                fwrite(&ch,sizeof(ch),1,eimage);
            }

        printf("\nEnter the text:");

        gets(sec_msg);

            char fileCh,msgCh='\0',writeCh;
            int count=0;
            fseek(eimage,100,SEEK_SET);
            for(count=0;count<=strlen(sec_msg);count++)
                {
                    fseek(eimage,100+(count*8),SEEK_SET);
                    for(int i=7;i>=0;i--)
                        {
                            msgCh=sec_msg[count];
                            msgCh=msgCh<<i;
                            msgCh=msgCh>>7;
                            fileCh=fgetc(eimage);
                            fseek(eimage,-1,SEEK_CUR);
                            writeCh=fileCh&254;
                            writeCh=writeCh|msgCh;
                            fputc(writeCh,eimage);
                        }
                }
            fseek(eimage,90,SEEK_SET);
            putw(count-1,eimage);
    }
    else
    {
        printf("FILE FORMAT NOT SUPPORTED!!");
    }
    fclose(eimage);

        scanf("%*c");
        printf("\n\nPress Enter to go back........");
        scanf("%*c");
    }

 decrypt()
    {
        system("cls");

        struct PIXEL dp;
        struct BMPFILEHEADER dbmp;

        char fpath[100];

        printf("\t\t\t\t\t  **************************************\n");
        printf("\t\t\t\t\t\t\tDECRYPTION\n");
        printf("\t\t\t\t\t  **************************************\n\n");

        FILE *dimage,*otp;

        printf("Enter the path of the file:");
        scanf("%s",fpath);
        dimage=fopen(fpath,"rb+");

        char *home;
        home=getenv("HOME");
        strcat(home,"/Secret.txt");
        otp=fopen(home,"w");

        unsigned char msgCh,fileCh,readCh;
        unsigned int lenOfStr;

        dbmp.filetype[0]=fgetc(dimage);
        dbmp.filetype[1]=fgetc(dimage);
            if(!strcmp(dbmp.filetype,"BM"))
                {
                    fseek(dimage,90,SEEK_SET);
                    lenOfStr=getw(dimage);
                    fseek(dimage,100,SEEK_SET);
                    for(int i=0;i<lenOfStr+1;i++)
                        {
                            msgCh='\0';
                            for(int j=7;j>=0;j--)
                                {
                                    fileCh=fgetc(dimage);
                                    readCh=fileCh<<7;
                                    readCh=readCh>>j;
                                    msgCh=msgCh|readCh;
                                }
                            fputc(msgCh,otp);
                        }
        printf("\n\n The hidden message is saved in a file Secret.txt in your home directory\n\n");
                }
            else
                {
                   printf("FILE FORMAT NOT SUPPORTED!!");
                }

        fclose(otp);
        fclose(dimage);

        scanf("%*c");
        printf("\n\nPress Enter to go back........");
        scanf("%*c");

    }

void main()
{
    while(1)
    {
        int opt;
        system("cls");
        printf("\t\t\t\t\t  **************************************\n");
        printf("\t\t\t\t\t\t\tSTEGNOGRAPHY\n");
        printf("\t\t\t\t\t  **************************************\n\n");

        printf("\n\n\t1. Encrypt the message");
        printf("\n\t2. Decrypt the message");
        printf("\n\t3. Quit");

        printf("\n\nEnter the option:");
        scanf("%d",&opt);

        if(opt==1)
           encrypt();
        else if(opt==2)
           decrypt();
        else if(opt==3)
           break;
        else
            printf("\n\tINVALID OPTION");
    }
}
