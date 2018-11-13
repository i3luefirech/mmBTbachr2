//
// Created by bluefire on 11/12/18.
//

#ifndef CODE_MMREALMOUSECTRL_H
#define CODE_MMREALMOUSECTRL_H

class mmRealMouseCtrl {
private:
    int mousefile;
    int buttonfile;
    struct input_event * ieMouse;
    struct input_event * ieButton;
public:
    mmRealMouseCtrl(void);
    int start(void *pVoid);
    void run(void *pVoid);
};

#endif //CODE_MMREALMOUSECTRL_H
