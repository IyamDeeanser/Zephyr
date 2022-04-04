#include "SD_Card.h"

//creates flight file
SDCard::SDCard()
{
    if (!SD.begin(/*chipselect*/)) {
    //write to telemetry that it isn't working
    //buzzer or some other signal
    }

    dataInitialize();
    settingsInitialize();

    return;
}

void SDCard::Log(const String & s)
{
    logcheck();

    if (dataFile && datalog) {
        dataFile = SD.open(datafilename, FILE_WRITE);
        dataFile.print(s);
        dataFile.close(); // close the file
    }
}

void SDCard::Logln(const String & s)
{
    logcheck();

    if (dataFile && datalog) {
        dataFile = SD.open(datafilename, FILE_WRITE);
        dataFile.print(s + '\n');
        dataFile.close(); // close the file
    }
}

void SDCard::SetRate(const float & n)
{
    dataSpacer = n;
}

// @ needs to be able to access totaltime
void SDCard::logcheck()
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

void SDCard::dataInitialize()
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

void SDCard::settingsInitialize()
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