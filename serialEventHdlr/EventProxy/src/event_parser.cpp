#include "event_parser.h"
#include "Arduino.h"

EventParser::EventParser()
{
   nbrOfAcceptedCmds = 0;
}

void EventParser::HandleEvent(C_Event& e)
{
   String evData = e.serializeData();
   ParseEvent(evData);
}

void EventParser::ParseEvent(String& unparsedData)
{
   if(nbrOfAcceptedCmds > 0)
   {
      int i = 0;
      CommandHandler *hdlr = nullptr;

      //fetch command
      while((hdlr == nullptr) && (i < nbrOfAcceptedCmds))
      {
         if (unparsedData.startsWith(commandHandlers[i]->cmd)) //data starts with a command
         {
            hdlr = commandHandlers[i]; // found handlerfor this command
         }

         i++;
      }

      if(hdlr != nullptr)
      {
         int cmd_length = hdlr->cmd.length();
         if (unparsedData.length() == cmd_length)
         {
            (*hdlr)();
         }

         // if the unparsed data contains more than the "cmd"-word, split out the data-part from the cmd-part
         // format is <cmd>_<data>"
         if ((unparsedData.length() > cmd_length + 1) && // does it contain data
             (unparsedData.charAt(cmd_length) == '_'))   // is the char after the "cmd" a '_'
         {
            String data = unparsedData.substring(cmd_length + 1); // take the data part, not the "cmd_"-part

            (*hdlr)(data);
         }
      }
   }
}

void EventParser::AddAcceptedCmd(CommandHandler &f)
{
   if (nbrOfAcceptedCmds < c_maxNbrOfAcceptedCmds)
   {
      commandHandlers[nbrOfAcceptedCmds] = &f;
      nbrOfAcceptedCmds++;
   }   
}

int EventParser::GetNbrOfAcceptedCmds()
{
   return nbrOfAcceptedCmds;
}