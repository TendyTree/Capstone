#include "parser.h"

Parser::Parser()
{

}
QString Parser::Parse_item(QString parse, QString command, bool start)
{
    /*
     * Things to parse out
     * ['0105\r'],#Coolant
     *     This will come back with euc the digit and the the 4105
     *     This then need to be converted to F
     * ['010C\r'],#rpm
     *      This will come back with euc the digit and the the 410C
     *      This then need to be converted to actual rpm which is byte converted to int then / 4
     * ['010D\r'],#Speed
     *      This will come back with euc the digit and the the 410D
     *      This will need to be converted to MPH
     * ['0144\r'],#Fuel air Command
     *      This will come back with euc the digit and the the 4144
     *      This will need to be converted to the maf equivalant
     * ['0146\r'],#Ambent air
     *      This will come back with euc the digit and the the 4146
     *      This will need to be converted to F
     * ['0149\r'],#Pedal Position
     *      This will come back with euc the digit and the the 4149
     * ['ATRV\r']#Volatge
     *      This will come back with euc the digit and the the __._v
     *      This will stay the same
     */
    if(start == false){
        if(command == "0105\r"){
            if(parse.contains("4105")){
                for(int i = 0; i <= parse.length(); i++){
                    repeat.append(parse.indexOf("4105"));
                    //check to see if it comes back -1
                    //if so break
                    //esle set i to index
                }
            }

        }else if(command == "010C\r"){

        }
    }else{
        /*
         * _Start_AT = [
         * ['ATZ\r'],
         *      This will come back with > If successful
         * ['ATD0\r'],
         * ['ATSP0\r'],
         * ['ATE0\r'],
         * ['ATH1\r'],
         * ['ATST64\r'],
         * ['ATS0\r'],
         * ['ATAT1\r'],
         * ['0100\r']
         */

    }
    return parsed;
}
