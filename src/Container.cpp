#include "header/Container.h"

SaveSlotContainer::SaveSlotContainer() {}

SaveSlotContainer::~SaveSlotContainer() {
    qDeleteAll(saveSlots);
}

void SaveSlotContainer::addSaveSlot(SaveSlot* slot) {
    saveSlots.append(slot);
}

void SaveSlotContainer::removeSaveSlot(SaveSlot* slot) {
    saveSlots.removeOne(slot);
}

SaveSlot* SaveSlotContainer::getSaveSlot(int index) {
    return saveSlots.at(index);
}

int SaveSlotContainer::size() {
    return saveSlots.size();
}

SaveSlotContainer::iterator::iterator(SaveSlotContainer* container, int index)
    : container(container), index(index) {}

SaveSlot* SaveSlotContainer::iterator::operator*() {
    return container->saveSlots.at(index);
}

SaveSlotContainer::iterator& SaveSlotContainer::iterator::operator++() {
    index++;
    return *this;
}

bool SaveSlotContainer::iterator::operator!=(const iterator& other) {
    return index != other.index;
}

SaveSlotContainer::iterator SaveSlotContainer::begin() {
    return iterator(this, 0);
}

SaveSlotContainer::iterator SaveSlotContainer::end() {
    return iterator(this, size());
}