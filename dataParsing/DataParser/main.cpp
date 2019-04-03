#include <QCoreApplication>
#include <QDebug>
/*
 * Andrew Brashich
 * Data Parser
 *
 * This console applitcation will have the function in it to parse the data recieved from the
 * ELM 327 and what to do with it. It will first take in the command so it knows what the last
 * message was sent then it will take the information in till it recieves a \r>. From there it
 * will parse the data to what it should be and then return the values. If there is more than
 * one value it will use the avg of them.
 *
 *
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList commands = { "0100", "0105","010C","010D","0144","0146","0149","ATRV"};
    QStringList split_returns;
    QStringList in;
    QTextStream msg(stdin);
    QString last_command;
    QString in_temp;

    qInfo() << "please enter the command that was last used";
    last_command = msg.readLine();
    qInfo() << "Command entered:" << last_command;
    while(true){
        qInfo() << "Please enter there the data:";
        in_temp = msg.readLine();
        in.append(in_temp);
        if(in_temp.endsWith("\r>")){
            break;
        }

    }

    return a.exec();
}
