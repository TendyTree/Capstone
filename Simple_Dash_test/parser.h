#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QVector>

class Parser
{
public:
    Parser();
    QString Parse_item(QString, QString, bool);
private:
    QVector<int> repeat;
    bool start;
    QString command;
    QString parse;
    QString parsed;

};

#endif // PARSER_H
