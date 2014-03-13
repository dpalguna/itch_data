#include "book_routines.h"
using namespace std;

int main()
{
 fstream input_file;
 timeStamp o_timeStamp;
 systemEventMessage o_systemEventMessage;
 stockDirectory o_stockDirectory;
 stockTradingAction o_stockTradingAction;
 regShoRestriction o_regShoRestriction;
 marketParticipantPosition o_marketParticipantPosition;
 addOrderMessage o_addOrderMessage;
 addOrderMessageAttribution o_addOrderMessageAttribution;
 orderExecutedMessage o_orderExecutedMessage;
 orderExecutedWithPriceMessage o_orderExecutedWithPriceMessage;
 orderCancelMessage o_orderCancelMessage;
 orderDeleteMessage o_orderDeleteMessage;
 orderReplaceMessage o_orderReplaceMessage;
 tradeMessageNonCross o_tradeMessageNonCross;
 tradeMessageCross o_tradeMessageCross;
 brokenTrade o_brokenTrade;
 netOrderImbalanceIndicator o_netOrderImbalanceIndicator;
 retailPriceImprovementIndicator o_retailPriceImprovementIndicator;

	
 cout<<endl<<sizeof(addOrderMessage);
cin.get();
 input_file.open("../S012714-v41.txt",ios::in | ios::binary);
 if(input_file ==  NULL)
   {
     exit(1);
   }
  else
   {  
     while(!input_file.eof())
      {
       char typeOfMessage;
       input_file.read((char*)&typeOfMessage,1);
       //cout<<endl<<"Msg:"<<typeOfMessage;
       /*if(typeOfMessage == '\0')
         {
          cout<<endl<<"Null message";
          cin.get();
         }*/
       switch(typeOfMessage)
        {
           case 'T': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_timeStamp,sizeof(timeStamp));
                     o_timeStamp.convert_endian();
                     o_timeStamp.print();
                     //cin.get();
                     break;
           case 'S': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_systemEventMessage,sizeof(systemEventMessage));
                     o_systemEventMessage.convert_endian();
                     o_systemEventMessage.print();
                     //cin.get();
                     break;
           case 'R': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_stockDirectory,sizeof(stockDirectory));
                     o_stockDirectory.convert_endian();
                     o_stockDirectory.print();
                     //cin.get();
                     break;
           case 'H': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_stockTradingAction,sizeof(stockTradingAction));
                     o_stockTradingAction.convert_endian();
                     o_stockTradingAction.print();
                     //cin.get();
                     break;
           case 'Y': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_regShoRestriction,sizeof(regShoRestriction));
                     o_regShoRestriction.convert_endian();
                     o_regShoRestriction.print();
                     //cin.get();
                     break;
           case 'L': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_marketParticipantPosition,sizeof(marketParticipantPosition));
                     o_marketParticipantPosition.convert_endian();
                     o_marketParticipantPosition.print();
                     //cin.get();
                     break;
           case 'A': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_addOrderMessage,sizeof(addOrderMessage));
                     o_addOrderMessage.convert_endian();
                     o_addOrderMessage.print();
                     //cin.get();
                     break;
           case 'F': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_addOrderMessageAttribution,sizeof(addOrderMessageAttribution));
                     o_addOrderMessageAttribution.print();
                     //cin.get();
                     break;
           case 'E': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderExecutedMessage,sizeof(orderExecutedMessage));
                     o_orderExecutedMessage.convert_endian();
                     o_orderExecutedMessage.print();
                     cin.get();
                     break;
           case 'C': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderExecutedWithPriceMessage,sizeof(orderExecutedWithPriceMessage));
                     o_orderExecutedWithPriceMessage.convert_endian();
                     o_orderExecutedWithPriceMessage.print();
                     cin.get();
                     break;
           case 'X': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderCancelMessage,sizeof(orderCancelMessage));
                     o_orderCancelMessage.convert_endian();
                     o_orderCancelMessage.print();
                     //cin.get();
                     break;
           case 'D': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderDeleteMessage,sizeof(orderDeleteMessage));
                     o_orderDeleteMessage.convert_endian();
                     o_orderDeleteMessage.print();
                     //cin.get();
                     break;
           case 'U': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderReplaceMessage,sizeof(orderReplaceMessage));
                     o_orderReplaceMessage.convert_endian();
                     o_orderReplaceMessage.print();
                     cin.get();
                     break;
           case 'P': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_tradeMessageNonCross,sizeof(tradeMessageNonCross));
                     o_tradeMessageNonCross.convert_endian();
                     o_tradeMessageNonCross.print();
                     cin.get();
                     break;
           case 'Q': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_tradeMessageCross,sizeof(tradeMessageCross));
                     o_tradeMessageCross.convert_endian();
                     o_tradeMessageCross.print();
                     cin.get();
                     break;
           case 'B': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_brokenTrade,sizeof(brokenTrade));
                     o_brokenTrade.convert_endian();
                     o_brokenTrade.print();
                     cin.get();
                     break;
           case 'I': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_netOrderImbalanceIndicator,sizeof(netOrderImbalanceIndicator));
                     o_netOrderImbalanceIndicator.convert_endian();
                     o_netOrderImbalanceIndicator.print();
                     cin.get();
                     break;
           case 'N': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_retailPriceImprovementIndicator,sizeof(retailPriceImprovementIndicator));
                     o_retailPriceImprovementIndicator.convert_endian();
                     o_retailPriceImprovementIndicator.print();
                     cin.get();
                     break;

           
           default: break;
        }

     }
   }
 input_file.close();
 
 return 0;
}

