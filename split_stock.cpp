#include "class_definitions.h"
using namespace std;

int main()
{
 fstream input_file,output_file;
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

 map<uint64_t, string> orderID_to_ticker;
 cout<<endl<<orderID_to_ticker.size();
 //cin.get();
 input_file.open("../S063010-v41.txt",ios::in | ios::binary);
 output_file.open("XOM",ios::out|ios::binary);
 if(input_file ==  NULL)
   {
     exit(1);
   }
  else
   {  
     bool end_of_day = 0;
     
     while(!end_of_day )
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
                     o_timeStamp.print();
                     o_timeStamp.convert_endian();
                     output_file.write((char*)&o_timeStamp,sizeof(timeStamp));
                     o_timeStamp.print();
                     cout<<endl<<orderID_to_ticker.size()<<" Map size";
                     end_of_day  = (o_timeStamp.second == 57600);
                     //cin.get();
                     break;
           case 'S': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_systemEventMessage,sizeof(systemEventMessage));
                     o_systemEventMessage.convert_endian();
                     output_file.write((char*)&o_systemEventMessage,sizeof(systemEventMessage));
                     //cin.get();
                     break;
           case 'R': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_stockDirectory,sizeof(stockDirectory));
                     o_stockDirectory.convert_endian();
                     if(o_stockDirectory.stock[0] == 'X' && o_stockDirectory.stock[1]=='O' 
                        && o_stockDirectory.stock[2] == 'M' && o_stockDirectory.stock[3] == ' '
                        && o_stockDirectory.stock[4] == ' ' && o_stockDirectory.stock[5] == ' '
                        && o_stockDirectory.stock[6] == ' ' && o_stockDirectory.stock[7] == ' ')
                        {
                          output_file.write((char*)&o_stockDirectory,sizeof(stockDirectory));
                        }

                     //cin.get();
                     break;
           case 'H': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_stockTradingAction,sizeof(stockTradingAction));
                     o_stockTradingAction.convert_endian();
                     if(o_stockTradingAction.stock[0] == 'X' && o_stockTradingAction.stock[1]=='O' 
                        && o_stockTradingAction.stock[2] == 'M' && o_stockTradingAction.stock[3] == ' '
                        && o_stockTradingAction.stock[4] == ' ' && o_stockTradingAction.stock[5] == ' '
                        && o_stockTradingAction.stock[6] == ' ' && o_stockTradingAction.stock[7] == ' ')
                        {
                          output_file.write((char*)&o_stockTradingAction,sizeof(stockTradingAction));
                        }

                     //cin.get();
                     break;
           case 'Y': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_regShoRestriction,sizeof(regShoRestriction));
                     o_regShoRestriction.convert_endian();
                     if(o_regShoRestriction.stock[0] == 'X' && o_regShoRestriction.stock[1]=='O' 
                        && o_regShoRestriction.stock[2] == 'M' && o_regShoRestriction.stock[3] == ' '
                        && o_regShoRestriction.stock[4] == ' ' && o_regShoRestriction.stock[5] == ' '
                        && o_regShoRestriction.stock[6] == ' ' && o_regShoRestriction.stock[7] == ' ')
                        {
                          output_file.write((char*)&o_regShoRestriction,sizeof(regShoRestriction));
                        }
                     //cin.get();
                     break;
           case 'L': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_marketParticipantPosition,sizeof(marketParticipantPosition));
                     o_marketParticipantPosition.convert_endian();
                     if(o_marketParticipantPosition.stock[0] == 'X' && o_marketParticipantPosition.stock[1]=='O' 
                        && o_marketParticipantPosition.stock[2] == 'M' && o_marketParticipantPosition.stock[3] == ' '
                        && o_marketParticipantPosition.stock[4] == ' ' && o_marketParticipantPosition.stock[5] == ' '
                        && o_marketParticipantPosition.stock[6] == ' ' && o_marketParticipantPosition.stock[7] == ' ')
                        {
                          output_file.write((char*)&o_marketParticipantPosition,sizeof(marketParticipantPosition));
                        }
                     
                     //cin.get();
                     break;
           case 'A': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_addOrderMessage,sizeof(addOrderMessage));
                     o_addOrderMessage.convert_endian();
                     if(o_addOrderMessage.stock[0] == 'X' && o_addOrderMessage.stock[1]=='O' 
                        && o_addOrderMessage.stock[2] == 'M' && o_addOrderMessage.stock[3] == ' '
                        && o_addOrderMessage.stock[4] == ' ' && o_addOrderMessage.stock[5] == ' '
                        && o_addOrderMessage.stock[6] == ' ' && o_addOrderMessage.stock[7] == ' ')
                        {
                          //o_addOrderMessage.print();	
                          output_file.write((char*)&o_addOrderMessage,sizeof(addOrderMessage));
                          orderID_to_ticker.insert(pair<uint64_t,string>
                          (static_cast<uint64_t>(o_addOrderMessage.OID), "XOM"));
                          //cout<<endl<<orderID_to_ticker.size();
                          //cin.get();
                        }
                     
                     //cin.get();
                     break;
           case 'F': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_addOrderMessageAttribution,sizeof(addOrderMessageAttribution));
                     o_addOrderMessageAttribution.convert_endian();
                     if(o_addOrderMessageAttribution.stock[0] == 'X' && o_addOrderMessageAttribution.stock[1]=='O' 
                        && o_addOrderMessageAttribution.stock[2] == 'M' && o_addOrderMessageAttribution.stock[3] == ' '
                        && o_addOrderMessageAttribution.stock[4] == ' ' && o_addOrderMessageAttribution.stock[5] == ' '
                        && o_addOrderMessageAttribution.stock[6] == ' ' && o_addOrderMessageAttribution.stock[7] == ' ')
                        {
                          //o_addOrderMessageAttribution.print();
                          output_file.write((char*)&o_addOrderMessageAttribution,sizeof(addOrderMessageAttribution));
                          orderID_to_ticker.insert(pair<uint64_t, string>
                          (static_cast<uint64_t>(o_addOrderMessageAttribution.OID), "XOM"));
                          //cout<<endl<<orderID_to_ticker.size();
 //cin.get();
                        }
                     break;
           case 'E': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderExecutedMessage,sizeof(orderExecutedMessage));
                     o_orderExecutedMessage.convert_endian();
                     if(orderID_to_ticker.find(o_orderExecutedMessage.OID) !=  orderID_to_ticker.end()
                        && orderID_to_ticker.find(o_orderExecutedMessage.OID)->second == "XOM")
                       {
                          output_file.write((char*)&o_orderExecutedMessage,sizeof(orderExecutedMessage));
                       }
                     break;
           case 'C': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderExecutedWithPriceMessage,sizeof(orderExecutedWithPriceMessage));
                     o_orderExecutedWithPriceMessage.convert_endian();
                     if(orderID_to_ticker.find(o_orderExecutedWithPriceMessage.OID) !=  orderID_to_ticker.end()
                        && orderID_to_ticker.find(o_orderExecutedWithPriceMessage.OID)->second == "XOM")
                       {
                          output_file.write((char*)&o_orderExecutedWithPriceMessage,sizeof(orderExecutedWithPriceMessage));
                       }
                    break;
           case 'X': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderCancelMessage,sizeof(orderCancelMessage));
                     o_orderCancelMessage.convert_endian();
                     if(orderID_to_ticker.find(o_orderCancelMessage.OID) !=  orderID_to_ticker.end()
                        && orderID_to_ticker.find(o_orderCancelMessage.OID)->second == "XOM")
                       {
                          output_file.write((char*)&o_orderCancelMessage,sizeof(orderCancelMessage));
                          //o_orderCancelMessage.print();
                       }
                     break;
           case 'D': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderDeleteMessage,sizeof(orderDeleteMessage));
                     o_orderDeleteMessage.convert_endian();
                     if(orderID_to_ticker.find(o_orderDeleteMessage.OID) !=  orderID_to_ticker.end()
                        && orderID_to_ticker.find(o_orderDeleteMessage.OID)->second == "XOM")
                       {
                          output_file.write((char*)&o_orderCancelMessage,sizeof(orderCancelMessage));
                          map<uint64_t, string>::iterator it = orderID_to_ticker.find(o_orderDeleteMessage.OID);
                          orderID_to_ticker.erase(it);
                          //o_orderDeleteMessage.print();
                       }
                     break;
           case 'U': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderReplaceMessage,sizeof(orderReplaceMessage));
                     o_orderReplaceMessage.convert_endian();
                     if(orderID_to_ticker.find(o_orderReplaceMessage.originalOID) !=  orderID_to_ticker.end()
                        && orderID_to_ticker.find(o_orderReplaceMessage.originalOID)->second == "XOM")
                       {
                          output_file.write((char*)&o_orderReplaceMessage,sizeof(orderReplaceMessage));
                          map<uint64_t, string>::iterator it = orderID_to_ticker.find(o_orderReplaceMessage.originalOID);
                          orderID_to_ticker.erase(it);
                          //o_orderReplaceMessage.print();
                          orderID_to_ticker.insert(pair<uint64_t,string>
                          (static_cast<uint64_t>(o_orderReplaceMessage.newOID), "XOM"));
                          //cout<<endl<<orderID_ticker_to.size();
 //cin.get();
                       }
                     break;
           case 'P': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_tradeMessageNonCross,sizeof(tradeMessageNonCross));
                     o_tradeMessageNonCross.convert_endian();
                     if(o_tradeMessageNonCross.stock[0] == 'X' && o_tradeMessageNonCross.stock[1]=='O' 
                        && o_tradeMessageNonCross.stock[2] == 'M' && o_tradeMessageNonCross.stock[3] == ' '
                        && o_tradeMessageNonCross.stock[4] == ' ' && o_tradeMessageNonCross.stock[5] == ' '
                        && o_tradeMessageNonCross.stock[6] == ' ' && o_tradeMessageNonCross.stock[7] == ' ')
                        {
                          output_file.write((char*)&o_tradeMessageNonCross,sizeof(tradeMessageNonCross));
                        }
                     break;
           case 'Q': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_tradeMessageCross,sizeof(tradeMessageCross));
                     o_tradeMessageCross.convert_endian();
                     if(o_tradeMessageCross.stock[0] == 'X' && o_tradeMessageCross.stock[1]=='O' 
                        && o_tradeMessageCross.stock[2] == 'M' && o_tradeMessageCross.stock[3] == ' '
                        && o_tradeMessageCross.stock[4] == ' ' && o_tradeMessageCross.stock[5] == ' '
                        && o_tradeMessageCross.stock[6] == ' ' && o_tradeMessageCross.stock[7] == ' ')
                        {
                          output_file.write((char*)&o_tradeMessageCross,sizeof(tradeMessageCross));
                        }
                     break;
           case 'B': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_brokenTrade,sizeof(brokenTrade));
                     o_brokenTrade.convert_endian();
                     //These messages can be ignored since we are only using ITCH data
                     break;
           case 'I': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_netOrderImbalanceIndicator,sizeof(netOrderImbalanceIndicator));
                     o_netOrderImbalanceIndicator.convert_endian();
                     if(o_netOrderImbalanceIndicator.stock[0] == 'X' && o_netOrderImbalanceIndicator.stock[1]=='O' 
                        && o_netOrderImbalanceIndicator.stock[2] == 'M' && o_netOrderImbalanceIndicator.stock[3] == ' '
                        && o_netOrderImbalanceIndicator.stock[4] == ' ' && o_netOrderImbalanceIndicator.stock[5] == ' '
                        && o_netOrderImbalanceIndicator.stock[6] == ' ' && o_netOrderImbalanceIndicator.stock[7] == ' ')
                        {
                          output_file.write((char*)&o_netOrderImbalanceIndicator,sizeof(netOrderImbalanceIndicator));
                        }
                     break;
           case 'N': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_retailPriceImprovementIndicator,sizeof(retailPriceImprovementIndicator));
                     o_retailPriceImprovementIndicator.convert_endian();
                     if(o_retailPriceImprovementIndicator.stock[0] == 'X' && o_netOrderImbalanceIndicator.stock[1]=='O' 
                        && o_netOrderImbalanceIndicator.stock[2] == 'M' && o_netOrderImbalanceIndicator.stock[3] == ' '
                        && o_netOrderImbalanceIndicator.stock[4] == ' ' && o_netOrderImbalanceIndicator.stock[5] == ' '
                        && o_netOrderImbalanceIndicator.stock[6] == ' ' && o_netOrderImbalanceIndicator.stock[7] == ' ')
                        {
                          output_file.write((char*)&o_netOrderImbalanceIndicator,sizeof(netOrderImbalanceIndicator));
                        }
                     break;
           default:  break;
        }

     }
   }
 input_file.close();
 output_file.close();
 
 return 0;
}

