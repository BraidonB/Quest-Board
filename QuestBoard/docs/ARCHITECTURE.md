## <u>QuestList</u>
Object that stores the quests in a list.

#### Variables

#### Methods
void pushBack  
void remove


## <u>Board</u>
Where the user goes to accept, view, and make quests.  

#### Variables
vector available  
vector unavailable  

#### Methods
void editQuest  
void addQuest  
void removeQuest  
void acceptQuest

## <u>Quest</u>
The task the user wants to complete.

#### Variables
int id  
int priority  
string name  
string description  
bool isCompleted  
vector prerequisites  

#### Methods
void setComplete  
void setIncomplete 