#include <stdio.h>
#include <assert.h>

void printColorCodeManualOnConsole(int colorCode,char* majorcolor,char* minorcolor)
{
    printf("%d | %s | %s\n",colorCode,majorColor,minorColor);
    //i * 5 + j, majorColor[i], minorColor[i]);
}

int printColorMap(void (*manualPrinter)(int colorCode,char* majorcolor,char* minorcolor)) {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            //printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]);
            manualPrinter(i * 5 + j,majorColor[i], minorColor[i]);     
        }
    }
    return i * j;
}
typedef struct
{
  int capturedColorCode;
  char* capturedMajorColor;
  char* capturedMinorColor;
}colorCodeManualItem;

colorCodeManualItem capturedManualList[25];

void fakeManualPrinterStub(int colorCode,char* majorcolor,char* minorcolor){
    capturedColorCode = colorCode;
    capturedMajorColor = majorcolor;
    capturedMinorColor = minorcolor; 
}
void fakeManualPrinterMock(int colorCode,char* majorcolor,char* minorcolor){
    colorCodeManualItem item={colorCode,majorcolor,minorcolor};
    capturedManualList[ colorCode] = item;
   
}
void test_cases()
{
    //Value based Testing
    int result=printColorMap(&fakeManualPrinterStub);
    assert(result == 25);

    //Interaction based Testing
    int result = printColorMap(&fakeManualPrinterMock);
    colorCodeManualItem expectedManualList[25];
    expectedManualList=
    assert(expectedManualList==capturedManualList);
}
int main() {
    int result = printColorMap(&printColorCodeManualOnConsole);
    
    assert(result == 16);
    printf("All is well (maybe!)\n");
    return 0;
}
