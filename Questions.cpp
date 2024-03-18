#include <iostream>
using namespace std;

#include <string.h>

/*
COMMON DATA TYPES, VARIABLES, ETC.

1. union - a block of memory that stores several data objects, 
but has only storage for the largest of these, 
and thus can only store one of the data objects at any one time.

2. struct - a block of memory that stores several data objects, where those objects don't overlap.

3. static - this keyword specifies a variables run time duration to last until the end of the program.
Once a static variable is declared, it can only be refrenced within the scope of the file it was defined in.

4. const -  A const variable cannot be modified once it is assigned. Once set, the variable/function
is stored in flash.

5. volatile - Specifies to the compiler that the variable might change outside of program control. This prevents
the compiler from optimizing the variable.

6. void * - can point to any variable that is not const or volatile. Void * cannot be 
dereferenced unless it is casted.

7. extern - Declares a variable has external linkage. The variable or function may be defined in a different
file but can be referenced using extern in a different file

8. % - The modulus operator yields the remainder from an integer division

9. & - Has two functions:
    a. Returns the address of a variable/function.
    b. Bitwise AND compares the bits of a variable and logical ANDs them.

10. enum - A set of named constants. By default, the first constant is set to zero
unless specified by the user.

*/

//#define Q1 // void *
//#define Q2 // allocating memory for a pointer
//#define Q3 // Swap Endian
//#define Q4 // Write 5 functions: setBit, clearBit, toggleBit, checkBit, and changeBit for int NUM
//#define Q5 // Set an integer variable at the absolute address 0x6789 to value 0xaabb
//#define Q6 // Count set bits in a number
//#define Q7 // Write a macro to swap bytes in 32bit integer variable
    //#define SWAP_BYTES(u32Val)    ((u32Val & 0xFF000000) >> 24)\
                                    |((u32Val & 0x00FF0000) >> 8)\
                                    |((u32Val & 0x0000FF00) << 8)\
                                    |((u32Val & 0x000000FF) << 24)
//#define Q8 // Recursive and Iterative Factorial
//#define Q9 // Recursive and Fibonnacci
//#define Q10 // Write a function that finds the last instance of a character
//#define Q11 // Allocate 10 INTS in memory and assign them values from 1 to 10;
//#define Q12 // Reverse an array. Any method
//#define Q13 // FIZZ BUZZ. Return a function array.
//#define Q14 // Create a Struct Union for a protocol
//#define Q15 // Write a function that converts Hexadecimal array bytes to decimal number
//#define Q16 // Write a recursive function that converts Hexadecimal string to decimal number
//#define Q17 // Write a function that converts a string to int
//#define Q18 // Create a Binary Search Tree
#define Q19 // Write a function pointer for add, sub, mult, and divide two ints and returns an int.

int setBit(int num, int bit){
    num |= (1UL << bit);              //  (X << Y) where X is setting the nth bit and Y is the bit number. (begins with bit 0)
    printf("num (setBit):%d\r\n", num);
    return num;
}
int clrBit(int num, int bit){
    num &= ~(1UL << bit);            // Shift 1 to Nth bit then invert and AND with NUM;
    printf("num (clrBit): %d\r\n", num);
    return num;
}
int toggleBit(int num, int bit){
    num ^= 1UL << bit;
    printf("num (toggle): %d\r\n", num);
    return num;
}
int countSetBits(int num){
    int count;
    for(count = 0; num; count++){
        num = num & (num - 1);
    }
    return count;
}
int factorialRecursive(int num){
    if(num == 0)
        return 0;
    if(num == 1)
        return 1;
    return num * factorialRecursive (num-1);
}
int factorialIterative(int num){
    int i;
    int sum = 1;
    if (num <= 1)
        return 1;
    for(i=num;num;num--){
        sum = sum*num;
    }
    return sum;
}
int fibonacciRecursive(int num){
    if(num <2)
        return 1;
    return fibonacciRecursive(num - 1) + fibonacciRecursive(num-2);
}
int *reverseArray(int num[], int size){
    int i;
    int temp;
    for(i=0;i<size/2;i++){
        temp = num[i];
        num[i] = num[size-i-1];
        num[size-i-1] = temp;
    }
    return num;
}

char* FizzBuzz(int start, int end, int &FBcount)
{
    static char FB[200];
    char num[10];
    const char *FizzBuzz = " FizzBuzz ";
    const char *Fizz = " Fizz";
    const char *Buzz = " Buzz";
    int i;
    
    for(start;start<end;start++)
    {
        if(start % 15 == 0)
        {
            for(i=0;i < 10;i++)
            {
                FB[FBcount++] = FizzBuzz[i];//printf(" FizzBuzz ");
                printf("[%d]: %c\n", FBcount-1, FB[FBcount-1]);
            }
        }
        else if(start % 3 == 0)
        {
            for(i=0;i<5;i++)//printf(" Fizz");
            {
                FB[FBcount++] = Fizz[i];
                printf("[%d]: %c\n", FBcount-1, FB[FBcount-1]);
            }
        }
        else if(start % 5 == 0)
        {
            for(i=0;i<5;i++)//printf(" Buzz");
            {
                FB[FBcount++] = Buzz[i];
                printf("[%d]: %c\n", FBcount-1, FB[FBcount-1]);
            }
        }
        else
        {
            FB[FBcount++] = start;
            printf("[%d] %d \n", FBcount-1, start);
        }
    }

    return FB;
}
//#pragma pack(1)
typedef union 
{
    uint8_t array_data[8];
    uint64_t id_value; __attribute__((packed));
}msg_product_id;

typedef union
{
    uint8_t array_data[100];
    struct
    {
        uint16_t id;
        uint8_t src;
        uint16_t icd_version __attribute__((packed));
        msg_product_id message_product_id __attribute__((packed));
        uint8_t timestamp[8];
        uint16_t data_payload_size __attribute__((packed));
        uint8_t data_payload[78];
    };
    
}OCB_message_payload;

typedef union 
{
    uint8_t data[108];
    struct 
    {
        uint8_t msg_source;
        uint8_t msg_destination;
        uint16_t msg_byte_count;

        OCB_message_payload message_payload;
        uint32_t crc;

    };
    
}OCB_message;

void hex_to_decimal(uint8_t *hexBytes)
{
    //printf("%d\n", hexBytes[0]);
    //printf("%d\n", hexBytes[1]);
    uint8_t hexBase = 16;
    uint8_t i; // power
    uint8_t count =0;
    unsigned long long result = 0;
    unsigned long long decResult = 0;

    for(i=0;i<16;i++)
    {
        if(i == 0)
        {
            result = 1;
        }
        else
            result *= hexBase;
        
        if(i%2 == 0)
        {
            decResult = decResult + result*(hexBytes[count] & 0x0F);
            //printf("%x decResult %llu ",hexBytes[count] & 0x0F, decResult);
        }
        else
        {
                decResult = decResult + result*(((hexBytes[count] & 0xF0) >> 4));
                //printf("%x decResult %llu ", ((hexBytes[count] & 0xF0) >> 4),decResult);
                count++;
        }
        //printf("16^%d = %llu == %llu\n", i, result, decResult);
        //printf("hexBytes[%d] == %x\n", i, hexBytes[i] & 0x0F);
        //printf("hexBytes[%d] == %x\n", i, (hexBytes[i] & 0xF0) >> 4);
    }
    printf("Hex to Decimal %llu\n", decResult);
}

long long power(int base, int n)
{
    long long result;
    if(n == 0)    // Base
    {
        return 1;
    }
    else    // Recursive procedure
    {
        result = base * power(base,n-1);
        printf("result: %llu\n", result);
        return result;
    }
}
void hex_to_decimal_recursive(uint8_t *hexBytes)
{
    //printf("%d\n", hexBytes[0]);
    //printf("%d\n", hexBytes[1]);
    uint8_t hexBase = 16;
    uint8_t i; // power
    uint8_t count =0;
    unsigned long long result = 0;
    unsigned long long decResult = 0;

    for(i=0;i<16;i++)
    {
                
        if(i%2 == 0)
        {
            decResult = decResult + power(16,i)*(hexBytes[count] & 0x0F);
            //printf("%x decResult %llu ",hexBytes[count] & 0x0F, decResult);
        }
        else
        {
                decResult = decResult + power(16,i)*(((hexBytes[count] & 0xF0) >> 4));
                //printf("%x decResult %llu ", ((hexBytes[count] & 0xF0) >> 4),decResult);
                count++;
        }
        //printf("16^%d = %llu == %llu\n", i, result, decResult);
        //printf("hexBytes[%d] == %x\n", i, hexBytes[i] & 0x0F);
        //printf("hexBytes[%d] == %x\n", i, (hexBytes[i] & 0xF0) >> 4);
    }
    printf("Hex to Decimal %llu\n", decResult);
}

unsigned long long ascii_to_int(uint8_t *num)
{
    unsigned long long result=0;
    int i;
    for(i=0;i<12;i++)
    {
        // 0 - 9
        if(num[i] >= '0' && num[i] <= '9')
           result = (result * 10) + (num[i] - '0');
    }
    
    return result;
}

/*
    Binary Search Tree
    A divide and conquer method to identify an element within a sorted array. Returns the index when the
    element is found. If not found, returns a -1.
    Params:
        arr = takes in a sorted array
        start = starting index
        end = end index
        element = element to search in the array
*/
int binary_search_tree (uint8_t *arr, int start, int end, int element)
{
    int mid;
    //printf("mid: %d\n", mid);
    while(start <= end) // when element is not found, start >= end
    {
        // Calculate the middle
        mid = start + ((end - start)/2); // middle = start + (end - start) / 2
        printf("middle: %d\n", mid);
        if(arr[mid] == element)
        {
            printf("arr[mid] == element: mid = %d\n", mid);
            return mid;
        }
        if (arr[mid] < element)
        {
            printf("start = mid + 1 = %d\n", mid + 1);
            start = mid + 1;
        }
        else 
        {
            printf("end = mid - 1 = %d\n", mid - 1);
            end = mid - 1;
        }
    }

    return -1; // didnt find the element
}

int Add(int x, int y) {return x+y;}
int Sub(int x, int y) {return x-y;}
int Mult(int x, int y){return x*y;}
int Div(int x, int y){return x/y;}
int Operation(int (*Func)(int, int), int x, int y) // Function that takes in a function pointer  and two ints
{
    return Func(x,y);
}
int main(){      
    

    #ifdef Q19
    // Use function pointer to perform operations!
    int sum, diff, prod, quot;
    sum = Operation(Add, 10, 5);
    diff = Operation(Diff, 10, 5);
    prod = Operation(Mult, 10, 5);
    quot = Operation(Div, 10, 5);

    printf("SUM: %d\n", sum);
    printf("DIFF: %d\n", diff);
    printf("PROD: %d\n", prod);
    printf("QUOT: %d\n", quot);
    
    #endif


    #ifdef Q18
    uint8_t arr[] = {1,2,4,8,16,32,64,128,255};
    int result;
    int start = 0;
    int element = 255;

    //printf("%d", sizeof(arr)/sizeof(int));
    result = binary_search_tree(arr, start, (sizeof(arr)/sizeof(uint8_t)) - 1, element);
    printf("result: %d", result);
    #endif

#ifdef Q17
// Convert string to int no array
uint8_t num[] = "123456789";

printf("%d\r\n", ascii_to_int(num));
#endif

#ifdef Q16
//hex to decimal using recursive
uint8_t hexBytes[] = {0x18, 0xDE, 0xAD, 0xBA, 0xBE, 0xFF, 0x11, 0x01};
hex_to_decimal_recursive(hexBytes);
#endif
#ifdef Q15
// Write a function that converts Hexadecimal array bytes to 8 byte decimal integer (little endian)
uint8_t hexBytes[] = {0x00,0x00,0xC8,0x21};//{0x18, 0xDE, 0xAD, 0xBA, 0xBE, 0xFF, 0x11, 0x01};

hex_to_decimal(hexBytes);
#endif

#ifdef Q14
                                   //               message     payload
                            //SRC   DST     Bcount   id    id   src  icd   icd                                           timestamp                             timestamp[7]   dataPayloadSize
    uint8_t output_buff[] ={0xD0, 0xD1, 0x11,0x03, 0x04,0x05, 0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,   0x11,  0x12   ,0x13,0x14,0x15,0x16,0x17,0x18,0x19,           0x1A,0xFF,          0xFA, 0x11, 0x22, 0x33, 0x44
    , 0x55, 0x66, 0x77, 0x88 , 0x99};
    uint8_t output_buff_length = sizeof(output_buff);
    OCB_message g_shost_received;

    memcpy(&g_shost_received.data, output_buff, output_buff_length);

    printf("size of output_buff: %d\n", output_buff_length);
    printf("Source:         %#06x\n", g_shost_received.msg_source);
    printf("Destination:    %#06x\n", g_shost_received.msg_destination);
    printf("MSG Byte Count: %#06x\n", g_shost_received.msg_byte_count);
    printf("ID: %#06x\n", g_shost_received.message_payload.id);
    printf("SRC: %#06x\n", g_shost_received.message_payload.src);
    printf("ICD Version: %#06x\n", g_shost_received.message_payload.icd_version);
    printf("UID: %#llx\n", g_shost_received.message_payload.message_product_id.id_value);
    for(int i=0;i<8;i++)
        printf("TimeStamp[%d]: %#x\n", i, g_shost_received.message_payload.timestamp[i]);
    printf("Data Payload Size: %#06x\n", g_shost_received.message_payload.data_payload_size);
    for(int i=0;i<10;i++)
        printf("Data Payload[%d]: %#02x\n", i,  g_shost_received.message_payload.data_payload[i]);

#endif
    

    
    #ifdef Q13
    // FIZZ BUZZ
    //Print integers one-to-N, but print “Fizz” if an integer is divisible by three, 
    //“Buzz” if an integer is divisible by five, and “FizzBuzz” if an integer is 
    //divisible by both three and five.
    char *st;
    int FBcount=0;

    st = FizzBuzz(1,20,FBcount);

    for(int i=0;i<FBcount;i++)
    {
        printf("%c", st[i]);
    }
    
    printf("count: %d\n", FBcount);
    #endif

    #ifdef Q12
    const int size = 12;
    int num[size] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int *r;
    r = reverseArray(num,size);
    for(int i=0;i<size;i++)
        printf("reverseArray[%d]:%d\r\n", i, r[i]);
    #endif
    #ifdef Q11
    int *num = (int*)malloc(sizeof(int)*10); // if string, add + 1 for terminating character
    int i;
    for(i=1;i<=10;i++){
        *num = i;
        printf("address: %d  num: %d\r\n", num, *num);
        num++; // increment by four because of INT = 4 bytes
    }
    #endif
    #ifdef Q10
    //const char *name="Derrek Velazquez";
    char *name = (char*)malloc(20);
    strcpy(name, "Derrek Velazquez1");
    char c;
    printf("name:%s\r\n", name);
    while(*name != '\0'){
        printf("Address: %d\t", name);
        printf("Character: %c\r\n", *name);
        name++;
    }
    name--;
    c = *name;
    printf("Last Character: %c\r\n", c);
    free(name);
    #endif
    #ifdef Q9
    printf("Fibonacci: %d\r\n", fibonacciRecursive(6));
    #endif
    #ifdef Q8
    printf("Factorial: %d\r\n", factorialIterative(5));
    #endif
    #ifdef Q7
    printf("Swap bytes: %#x\r\n", SWAP_BYTES(0xAABBCCDD));
    #endif
    #ifdef Q6
    printf("set bits: %d\r\n", countSetBits(63));
    #endif
    #ifdef Q5
    int *num;
    int q = 90;
    num = &q;

    printf("address: %#x\r\n", &num); // use & to get address
    printf("value: %d\r\n", *num);    // derefrence the pointer to get the value
    #endif
    #ifdef Q4
    int num;
    num = setBit(1, 3);
    num = clrBit(num,3);
    num = toggleBit(num,3);
    num = toggleBit(num,3);

    #endif

    #ifdef Q3
    unsigned int num1 = 0xFFBBAACC;
    unsigned int swapEndian;

    swapEndian = (0x000000FF & num1) << 24;
    printf("endian: %#x\r\n", swapEndian);
    swapEndian |= (0x0000FF00 & num1) << 8;
    printf("endian: %#x\r\n", swapEndian);
    swapEndian |= (0x00FF0000 & num1)  >> 8;
    printf("endian: %#x\r\n", swapEndian);
    swapEndian |= (0xFF000000 & num1) >> 24;

    printf("num1: %#x\r\n", num1);
    printf("endian: %#x\r\n", swapEndian);
    #endif


    #ifdef Q2
    char *name ;
    name = (char*) malloc(8); // allocate storage
    strcpy(name, "derrek");
    int n = strlen(name);

    printf("n = %d", n);
    printf("name: %s\r\n", name);
    free(name);
    #endif
    
    
    #ifdef Q1
    int a[] = {4, 3, 9, 10, 77, 88};
    void *ptr;
    ptr = &a; // for void pointers you need to provide the & because it doesn't know the type

    ptr=ptr + sizeof(int); // increase the pointer by 4 bytes since ptr address == 4 bytes
    printf("void pointer value :%d\r\n", *(int*)ptr); // for voids only *(int*)
    #endif


    return 0;
}