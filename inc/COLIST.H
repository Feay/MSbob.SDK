/////////////////////////////////////////////////////////////////////////////
// UCoList
//
// This container class works the same as the MFC class CPtrList, except
// that it is tuned for Component Objects.  It AddRefs any objects as they
// are added to the collection and Releases them as they are removed.
//
// History:
// 03-25-93 DarrinM     Created.
// 05-04-93 FordM       Copy Constructor.
/////////////////////////////////////////////////////////////////////////////

#ifndef __COLIST_H__
#define __COLIST_H__

class UCoList : public CPtrList
{
public:
// Operations
    // copy constructor - add each element to new list and AddRef
    UCoList(UCoList & lsco) { 
        CPtrList::RemoveAll();
        POSITION pos = lsco.GetHeadPosition();
        while (pos != NULL)        
            AddTail((IUnknown *)lsco.GetNext(pos));
    }
    
    // default constructor - required since copy constructor is defined
    UCoList() : CPtrList() {};

    // get head or tail (and remove it) - don't call on empty list !
    IUnknown* RemoveHead() {
        IUnknown *punk;
        punk = (IUnknown *)CPtrList::RemoveHead();
        punk->Release();
        return punk;
    }   
    IUnknown* RemoveTail() {
        IUnknown *punk;
        punk = (IUnknown *)CPtrList::RemoveTail();
        punk->Release();
        return punk;
    }   

    // add before head or after tail
    POSITION AddHead(IUnknown* newElement) {
        newElement->AddRef();
        return CPtrList::AddHead(newElement);
    }
    POSITION AddTail(IUnknown* newElement) {
        newElement->AddRef();
        return CPtrList::AddTail(newElement);
    }   

    // remove all elements
    void RemoveAll() {
        POSITION pos;
        pos = GetHeadPosition();
        while (pos != NULL)
            ((IUnknown *)GetNext(pos))->Release();
        CPtrList::RemoveAll();
    }   

    // getting/modifying an element at a given position
    void SetAt(POSITION pos, IUnknown* newElement) {
        ((IUnknown *)GetAt(pos))->Release();
        newElement->AddRef();
        CPtrList::SetAt(pos, newElement);
    }   
    void RemoveAt(POSITION pos) {
        ((IUnknown *)GetAt(pos))->Release();
        CPtrList::RemoveAt(pos);
    }   

    // inserting before or after a given position
    POSITION InsertBefore(POSITION pos, IUnknown* newElement) {
        newElement->AddRef();
        return CPtrList::InsertBefore(pos, newElement);
    }
    POSITION InsertAfter(POSITION pos, IUnknown* newElement) {
        newElement->AddRef();
        return CPtrList::InsertAfter(pos, newElement);
    }
};

#endif  // ifndef __COLIST_H__