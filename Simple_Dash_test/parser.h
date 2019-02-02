#ifndef PARSER_H
#define PARSER_H

#include <QString>

class Parser
{
public:
    Parser();
    QString Parse_item(QString, QString, bool);
private:
    bool start;
    QString command;
    QString parse;
    QString parsed;

};

#endif // PARSER_H
