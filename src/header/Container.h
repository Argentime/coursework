#pragma once

#include <QVector>
#include "SaveSlot.h"

class SaveSlotContainer {
public:
    SaveSlotContainer();
    ~SaveSlotContainer();

    void addSaveSlot(SaveSlot* slot);
    void removeSaveSlot(SaveSlot* slot);
    SaveSlot* getSaveSlot(int index);
    int size();

    class iterator {
    public:
        iterator(SaveSlotContainer* container, int index);
        SaveSlot* operator*();
        iterator& operator++();
        bool operator!=(const iterator& other);
        int index;

    private:
        SaveSlotContainer* container;
        
    };

    iterator begin();
    iterator end();

private:
    QVector<SaveSlot*> saveSlots;
};
