#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct {
    int capturedColorCode;
    const char* capturedMajorColor;
    const char* capturedMinorColor;
} colorCodeManualItem;

colorCodeManualItem capturedManualList[25];

void printColorCodeManualOnConsole(int colorCode, const char* majorColor, const char* minorColor) {
    printf("%d | %s | %s\n", colorCode, majorColor, minorColor);
}

int printColorMap(void (*manualPrinter)(int colorCode, const char* majorColor, const char* minorColor)) {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            manualPrinter(i * 5 + j, majorColor[i], minorColor[j]);
        }
    }
    return i * j;
}

void fakeManualPrinterStub(int colorCode, const char* majorColor, const char* minorColor) {
    // No logic needed for the stub, just a placeholder
}

void fakeManualPrinterMock(int colorCode, const char* majorColor, const char* minorColor) {
    colorCodeManualItem item = {colorCode, majorColor, minorColor};
    capturedManualList[colorCode] = item;
}

void test_cases() {
    // Value-based Testing
    int result = printColorMap(&fakeManualPrinterStub);
    assert(result == 25);

    // Interaction-based Testing
    result = printColorMap(&fakeManualPrinterMock);

    colorCodeManualItem expectedManualList[25];
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int code = i * 5 + j;
            expectedManualList[code].capturedColorCode = code;
            expectedManualList[code].capturedMajorColor = majorColor[i];
            expectedManualList[code].capturedMinorColor = minorColor[j];
        }
    }

    for (int k = 0; k < 25; k++) {
        assert(expectedManualList[k].capturedColorCode == capturedManualList[k].capturedColorCode);
        assert(strcmp(expectedManualList[k].capturedMajorColor, capturedManualList[k].capturedMajorColor) == 0);
        assert(strcmp(expectedManualList[k].capturedMinorColor, capturedManualList[k].capturedMinorColor) == 0);
    }
}

int main() {
    test_cases();
    int result = printColorMap(&printColorCodeManualOnConsole);
    printf("All is well (maybe!)\n");
    return 0;
}
