#include <iostream>

using namespace std;
struct Stack
{
    int info;
    Stack *next;
};
////////////////////////Дополнительные функции интерфейса////////////////
void error_message()
{
    cout<<"*** Симплетрон аварийно завершил выполнение программы ***"<<endl;
}
//////////////////////Основные функции///////////////////////////////////

void write_commands(short memory[100])
{
    short n;
    int i=0;
    while(true)
    {

        if(i<10)
            cout<<'0'<<i<<"? +";
        else
            cout<<i<<"? +";
        cin>>n;
        if(n==9999)
            break;
        else
        {

            memory[i]=n;
            ++i;
        }
    }
}
void  read_command(short memory[100],short &opCode,short &operand,short &inReg,short &inCount)
{
    inReg=memory[inCount];
    opCode=inReg/100;
    operand=inReg%100;
    ++inCount;
}
void read(short memory[100], short operand,bool FE)
{

    int n;
    cout<<endl<<"*** Введите данные ***"<<endl<<"> ";
    cin>>n;
    if (n>9999 || n<-9999)
    {
        cout<<"*** Слишком большая величина ***"<<endl;
        error_message();
        FE=true;
    }
    else
        memory[operand]=n;
}
void write(short memory[100],short operand)
{
    cout<<memory[operand];
}
void load(short memory[100],short operand,short &accumulator)
{
    accumulator=memory[operand];
}

void store(short memory[100],short operand,short &accumulator)
{
    memory[operand]=accumulator;
}
void add(short memory[100],short operand,short &accumulator,bool &FE)
{
    if((accumulator+memory[operand])>9999)
    {
        cout<<"*** Аккумулятор переполнен ***";
        error_message();
        FE=true;
    }
    else
        accumulator+=memory[operand];
}
void subtract(short memory[100],short operand,short &accumulator,bool &FE)
{
    if((accumulator-memory[operand])<-9)
    {
        cout<<"*** Аккумулятор переполнен ***";
        error_message();
        FE=true;
    }
    else
        accumulator-=memory[operand];

}
void divide (short memory[100],short operand,short &accumulator,bool &FE)
{
    if (0==memory[operand])
    {
        cout<<"*** Попытка деления на ноль ***";
        error_message();
        FE=true;

    }
    else accumulator/=memory[operand];

}
void multiply(short memory[100],short operand,short &accumulator,bool &FE)
{
    if((accumulator*memory[operand])<-9999||(accumulator*memory[operand])>9999)
    {
        cout<<"*** Аккумулятор переполнен ***";
        error_message();
        FE=true;
    }
    else
        accumulator*=memory[operand];
}
void branch(short operand,short &inCount)
{
    inCount=operand;
}
void branchNEG(short operand,short &inCount,short accumulator)
{
    if(accumulator<0)
        inCount=operand;

}
void branchZERO(short operand,short &inCount,short accumulator)
{
    if(accumulator==0)
        inCount=operand;

}
bool halt (bool &FE)
{
    FE=true;
    return 0;

}
///////////////Функции, необходимые для стека вызовов////////////////////
void push(Stack *&pStack,int info)
{
    Stack *tmp = new Stack;
    tmp->info=info;
    tmp->next=pStack;
    pStack=tmp;
}
int pop(Stack *&pStack)
{
    int zuzu=pStack->info;
    Stack *tmp=pStack;
    pStack=pStack->next;
    delete tmp;
    return zuzu;
}
void function_begin(short accum,short operand,short &inCount,Stack *&Stack)
{
    push(Stack,accum);
    push(Stack,inCount);
    inCount=operand;
}
void function_end(short &accum,short &inCount,Stack *&Stack)
{
    inCount=pop(Stack);
    accum=pop(Stack);
}
void line()
{
    for(int i=0; i<111; ++i)
        cout<<'_';
    cout<<endl;
}
void write_damp(short *memory, short accumulator, short instructionCounter, short instructionRegister, short operationCode, short operand)
{
    cout<<endl<<"РЕГИСТРЫ:"<<endl;
    cout<<"accumulator          ";
    cout.width(10);
    cout<<accumulator<<endl;
    cout<<"instructionCounter   ";
    cout.width(10);
    cout<<instructionCounter<<endl;
    cout<<"instructionRegister  ";
    cout.width(10);
    cout<<instructionRegister<<endl;
    cout<<"operationCode        ";
    cout.width(10);
    cout<<operationCode<<endl;
    cout<<"operand              ";
    cout.width(10);
    cout<<operand<<endl;

    cout<<"ПАМЯТЬ:"<<endl<<"  ";
    for(short i=0; i<10; ++i)
        cout<<"     "<<i;
    cout<<endl<<" ";
    for(short j=0; j<91;)
    {
        cout<<j;
        j+=10;
        for(int a=j-10; a<j; ++a)
        {
            cout<<" ";
            cout.width(5);
            cout<<memory[a];
        }
        cout<<endl;
    }
}

/////////////////////////////////////////////////////////////////////////

int main()
{

    Stack *Stack=NULL;
    short accumulator,memory[100]= {0};
    short instructionCounter=0;
    short operationCode;//Код текущей исполняемой операции
    short operand;//адрес яйчейки, над которой мы оперируем
    short instructionRegister;//текущая исполняемая команда
    bool fatal_error=false;
    cout<<"*** Симплетрон приветствует вас! ***"<<endl
        <<"*** Пожалуйста, введите вашу программу по одной команде ***"<<endl
        <<"*** (или слову данных) за раз. Я буду выводить в качестве ***"<<endl
        <<"*** подсказки текущий адрес и знак вопроса (?). Введённое ***"<<endl
        <<"*** вами слово будет размещено по указанному адресу. Для ***"<<endl
        <<"*** прекращения ввода программы введите число 9999 ***"<<endl;
    line();
    write_commands(memory);
    line();
    cout<<"*** Загрузка программы завершена ***"<<endl
        <<"*** Начинаю выполнение программы ***"<<endl;

    while(!fatal_error)
    {
        read_command(memory,operationCode,operand,instructionRegister,instructionCounter);
        cout<<"_____________________________"<<endl<<"branch Zero: "<<endl;
    cout<<"Accumulator: "<<accumulator<<endl;
    cout<<"InCount: "<<instructionCounter<<endl;
    cout<<"operand: "<<operand<<endl;
    cout<<"  97:"<<memory[97]<<endl<<" 98: "<<memory[98]<<endl<<"  99:"<<memory[99]<<endl
        <<"_______________________________";
        switch(operationCode)
        {
        case 10:
            read(memory,operand,fatal_error);
            break;
        case 11:
            write(memory,operand);
            break;
        case 20:
            load(memory,operand,accumulator);
            break;
        case 21:
            store(memory,operand,accumulator);
            break;
        case 30:
            add(memory,operand,accumulator,fatal_error);
            break;
        case 31:
            subtract(memory,operand,accumulator,fatal_error);
            break;
        case 32:
            divide(memory,operand,accumulator,fatal_error);
            break;
        case 33:
            multiply(memory,operand,accumulator,fatal_error);
            break;
        case 40:
            branch(operand,instructionCounter);
            break;
        case 41:
            branchNEG(operand,instructionCounter,accumulator);
            break;
        case 42:
            branchZERO(operand,instructionCounter,accumulator);
            break;
        case 43:
            halt(fatal_error);
            break;
        case 50:
            function_begin(accumulator,operand,instructionCounter,Stack);
            break;
        case 51:
            function_end(accumulator,instructionCounter,Stack);
            break;
        }
    }
    write_damp(memory, accumulator, instructionCounter,instructionRegister,operationCode, operand);
    return 0;
}
