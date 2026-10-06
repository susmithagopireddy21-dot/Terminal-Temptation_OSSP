SKILL 2 – CONTROL FLOW DIAGRAM

START
  |
  v
Save Original Terminal Settings
  |
  v
Enable Raw Mode
  |
  v
Display Program Menu
  |
  v
Display Prompt ">"
  |
  v
Initialize Input Buffer
  |
  v
Read Keyboard Character
  |
  v
+---------------------------+
| Is Enter Pressed?         |
+---------------------------+
       | Yes
       v
Terminate Input String
       |
       v
Process Command
       |
       v
+---------------------------+
| Is command "exit"?        |
+---------------------------+
    | Yes              | No
    v                  v
Display Exit       Check Command
Message                |
    |                  v
    |          +--------------------+
    |          | help / hello /     |
    |          | other / empty      |
    |          +--------------------+
    |                  |
    |                  v
    |          Display Result
    |                  |
    |                  v
    |          Return to Prompt
    |                  |
    +--------->---------+
              |
              v
      Restore Terminal
              |
              v
             END


If Enter is NOT pressed:
              |
              v
+---------------------------+
| Is Backspace Pressed?     |
+---------------------------+
       | Yes          | No
       v              v
Remove Last      Add Character
Character        to Buffer
       |              |
       +------>-------+
              |
              v
       Read Next Character
