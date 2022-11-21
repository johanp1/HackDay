#include "model.h"

Model::Model()
{
   x_pos_ = 0.0f;
   z_pos_ = 0.0f; 
   spindle_speed_ = 0;
   active_axis_ = axis_x; 

   for(int i = 0; i < k_maxNbrOfObservers; i++)
   {
      registry_[i] = nullptr;
   }
};

void Model::Attach(Observer* o)
{
   int i = 0;
   bool found  = false;

   // look for empty spot to place new observer
   while ((!found) && (i < k_maxNbrOfObservers))
   {
      if(registry_[i] == nullptr)
      {
         registry_[i] = o;
         found = true;
      }
      i++;
   }
};

void Model::Detach(Observer* o)
{
   int i = 0;
   bool found  = false;

   // look for observer to detach
   while ((!found) && (i < k_maxNbrOfObservers))
   {
      if (registry_[i] == o)
      {
         registry_[i] = nullptr;
         found = true;
      }
      i++;
   }
};

void Model::Notify()
{
   for(int i = 0; i < k_maxNbrOfObservers; i++)
   {
      if(registry_[i] != nullptr)
      {
         registry_[i]->Update();
      }
   }
};
