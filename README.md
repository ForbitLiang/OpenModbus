
# OpenModbus
---
## Introduce
This module can only be in slave mode at present, has TCP and RTU functions, and the function code only supports register operations·
This module has the following features in terms of functionality
- Build only for the application layer
- Lower coupling between sub modules
- Stronger availability

Refer-Thank you!
- freemodbus
- 《Modbus协议中文版【完整版】.pdf》

## file description
- V1.0:source code
    - modbus_SelfTEST.xlsx:self test record.
    - modbus_fileReferenceDiagram.eddx:...(open by eddx)
    - testcode.c:test,data associate with file of 'modbus_SelfTEST.xlsx'.
- refer
    - freemodbus-v1.6:official source code
        - freemodbus_fileReferenceDiagram.eddx: ...(open by eddx)
        - freemodbus_stateMachineDiagram.eddx:...(open by eddx)
    - Modbus协议中文版【完整版】.pdf

## How to use?
Supports any platform with a C environment. For demos, please temporarily refer to 'testcode.c'.
