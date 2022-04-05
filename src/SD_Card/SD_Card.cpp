#include "SD_Card.h"

//creates flight file
SD_Card::SD_Card()
{
    if (!SD.begin(/*chipselect*/)) {
        Serial1.println("");
    //buzzer or some other signal
    }

    dataInitialize();
    settingsInitialize();
}

void SD_Card::Log(const String & s)
{
    logcheck();

    if (dataFile && datalog) {
        dataFile = SD.open(datafilename, FILE_WRITE);
        dataFile.print(s);
        dataFile.close(); // close the file
    }
}

void SD_Card::Logln(const String & s)
{
    logcheck();

    if (dataFile && datalog) {
        dataFile = SD.open(datafilename, FILE_WRITE);
        dataFile.print(s + '\n');
        dataFile.close(); // close the file
    }
}

void SD_Card::SetRate(const float & n)
{
    dataSpacer = n;
}

// @ needs to be able to access totaltime
void SD_Card::logcheck()
{
    if(logDelay)
    {
        if((totalTime-counter) > dataSpacer)
        {
            datalog = true;
            counter = totalTime;
        }
        else
        {
            datalog = false;
        }
    }
}

void SD_Card::dataInitialize()
{
    filenum = 1;
    while(true) 
    {
        sprintf(datafilename, "Flight_%d.csv", filenum);
        if(!SD.exists(datafilename)) {
            break;
        }
        else {
            filenum++;
        }
    }

    dataFile = SD.open(datafilename, FILE_WRITE);

    // if the file opened okay, write the csv headings to it:
    if (dataFile) {
        dataFile.print("/*datatype here*/");
        dataFile.println(/*last dataset*/);

    // close the file:
        dataFile.close();
    }
    else {
        // if the file didn't open, send an error
    }
}

void SD_Card::settingsInitialize()
{
    if(settingsWrite)
    {
        //filewriting names
        sprintf(settingsfilename, "Settin_%d.csv", filenum);

        settingsFile = SD.open(settingsfilename, FILE_WRITE);
        
        // if the file opened okay, write to it:
        if (settingsFile) {
            settingsFile.print(/*"dataname"*/); settingsFile.println(/*data*/);

            // close the file:
            settingsFile.close();
        }
        
        else {
        // if the file didn't open, print an error:
        }
        settingsWrite = false; 
    }
}