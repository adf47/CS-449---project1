//Antonino Febbraro
//Project 1 Part 2 --- EXIF Viewer of JPEG
//Due Date: October 2nd, 2016


#include <stdio.h>

struct HeaderInfo //Struct fof JPEG/TIFF/EXIF header
{
    //use this struct to check for file errors 
    unsigned short fileStart;
    unsigned short app1; //this is the only thing needed/useful from this struct
    unsigned short APP0;
    unsigned char exif[4]; //String for exif
    unsigned short byte0;
    unsigned short endianess;
    unsigned short version;
    unsigned int offset;
};

struct Tiff //Struct for tiff tag
{
    unsigned short tag;
    unsigned short type;
    unsigned int items;
    unsigned int value;
};



int main(int argc, char **argv){
    
    //Data that we want to grab for the exif viewer
    //Data that is displayed with printf() func
    unsigned char manufactuer[40]; //string
    unsigned char Model[40]; //String
    unsigned int exposureNumerator;
    unsigned int exposureDenominator;
    unsigned int lensNumerator;
    unsigned int lensDenominator;
    unsigned char dateTaken[40]; //String
    unsigned int width;
    unsigned int height;
    unsigned int fStopNumerator;
    unsigned int fStopDenominator;
    unsigned short ISO;
    float fstop;
    
    
    
    FILE *file = fopen(argv[1],"rb"); //opening the file to be read.
    
   
    
    struct HeaderInfo header;
    fread(&header,sizeof(header),1,file); //reading header info from file
    unsigned short count; //this is the count of the offset as describe in project description
    fread(&count,2,1,file); //getting offest 20 for count
    
    struct Tiff tiff;
    
    
    if(header.app1 == 0xE0FF){ //meaning that this is APP0
        printf("APPO found. Not Supported.\n");
        return 0;
    }
    
    if(!strcmp(header.exif,"exif")){ //checking if exif string is in the right place
        printf("Exit Viewer error. The exif tag was not found. \n");
        return 0;
    }
    
    
    if(header.endianess != 18761){ //checking to make sure the right endianness is used, meaing endianess is MM -- error
        printf("Error. MM endianess is not supported. \n");
        return 0;
    }
    
    int x = 0;
    
    while(x<count){
        
        
        fread(&tiff,sizeof(tiff),1,file);
        int pos = ftell(file); //stores position of beginning of tiff block
        
        if(tiff.tag == 0x010F){ //get the manufacturer data here
            
            int pos = ftell(file); //stores position of beginning of tiff block
            fseek(file,tiff.value+12,SEEK_SET);
            
            int y = 0;
            
            while(y<tiff.items){
                
                manufactuer[y] = getc(file);
                y++;
            }
            
            fseek(file,pos,SEEK_SET);
            
        }
        else if(tiff.tag == 0x0110){ //get info for camera model here
            
            int pos = ftell(file); //stores position of beginning of tiff block
            fseek(file,tiff.value+12,SEEK_SET);
            
            int y = 0;
            
            while(y<tiff.items){
                
                Model[y] = getc(file);
                y++;
            }
            
            
            fseek(file,pos,SEEK_SET);
            
        }
        else if(tiff.tag == 0x8769){
            
            fseek(file,tiff.value+12,SEEK_SET);
            break; //since this is the end of this block
            
        }
        
        x++;
        
    }
    
    fread(&count,2,1,file); //read tiff count for the next block of data -- to see where items are stored
    
    
    x= 0;
    
    while(x<count){ //reading second block here
        
        
        fread(&tiff,sizeof(tiff),1,file);
        
        if(tiff.tag == 0xA002){ //get the width info here
           
            int pos2 = ftell(file);
            width = tiff.value;
            
        }
        else if(tiff.tag == 0xA003){ //get the Height infor here
            
            int pos2 = ftell(file);
            height = tiff.value;
            
        }
        else if(tiff.tag == 0x8827){ //get the Height info for IOS Speed here
            
            int pos2 = ftell(file);
            ISO = tiff.value;
            
        }
        else if(tiff.tag == 0x829D){ //getting info for F-Stop here
            
            int pos2 = ftell(file);
            fseek(file,tiff.value+12,SEEK_SET); // resetting the offset to get to denominator
            fread(&fStopNumerator,4,1,file);
            fread(&fStopDenominator,4,1,file);
            fseek(file,pos2,SEEK_SET);
            
            fstop = (float)fStopNumerator/fStopDenominator; //calculating fstop
            
        }
        else if(tiff.tag == 0x829A){ //exposure speed info here
            
            int pos2 = ftell(file);
            fseek(file,tiff.value+12,SEEK_SET); // resetting the offset to get to denominator
            fread(&exposureNumerator,4,1,file);
            fread(&exposureDenominator,4,1,file);
            fseek(file,pos2,SEEK_SET);
            
            
        }
        else if(tiff.tag == 0x920A){
            
            int pos2 = ftell(file);
            fseek(file,tiff.value+12,SEEK_SET); // resetting the offset to get to denominator
            fread(&lensNumerator,4,1,file);
            fread(&lensDenominator,4,1,file);
            fseek(file,pos2,SEEK_SET);
            
        }
        else if(tiff.tag == 0x9003){ //info for the date taken here
            
            int pos2 = ftell(file);
            int y = 0;
            
            fseek(file,tiff.value+12,SEEK_SET);
            
            while(y<tiff.items){
                
                dateTaken[y] = getc(file);
                y++;
            }
            
            fseek(file,pos2,SEEK_SET);
            
        }
        
        
        x++;
        
    }
    
    
    //Printing out the data from the file
    printf("Manufactuer: \t%s\n",manufactuer);
    printf("Model: \t\t%s\n",Model);
    printf("Exposure Time: \t%d/%d Second\n",exposureNumerator,exposureDenominator);
    printf("F-Stop: \tf/%0.1f\n",fstop);
    printf("ISO: \t\tISO %d\n",ISO);
    printf("Date Taken: \t%s\n",dateTaken);
    printf("Focal Length: \t%dmm\n",lensNumerator);
    printf("Width: \t\t%d pixels\n",width);
    printf("Height: \t%d pixels\n",height);
    
    //Close the file -- end of file
    fclose(file);
    
    
    return 0; //ending the program.
}
