#ifndef BOTNETIDS_BASICID_BASICID_H_
#define BOTNETIDS_BASICID_BASICID_H_

class BasicID {
public:
    BasicID();
    BasicID(BasicID* id);
    BasicID(int id);
    virtual ~BasicID();
    int getBasicID() const;
    void setBasicID(int id);
    bool isSet();
private:
    int basicID;
};

#endif /* BOTNETIDS_BASICID_BASICID_H_ */
