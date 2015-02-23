#pragma once

#include "EventSubscriber.h"

namespace SOUI
{

    class SEvent
    {
    public:
        SEvent(DWORD dwEventID,LPCSTR pszEventHandlerName):m_dwEventID(dwEventID),m_strEventHanderName(pszEventHandlerName)
        {

        }

        ~SEvent()
        {
            for(UINT i=0;i<m_evtSlots.GetCount();i++)
            {
                delete m_evtSlots[i];
            }
            m_evtSlots.RemoveAll();
        }

        DWORD GetEventID(){return m_dwEventID;}

        SStringA GetEventHandlerName() const {return m_strEventHanderName;}
        /*!
        \brief
            Subscribes some function or object to the Event

        \param SlotFunctorBase
            A function, static member function, or function object, with the
            signature void function_name(const EventArgs& args). 

        \return void
        */
        bool subscribe(const ISlotFunctor& slot);

        bool unsubscribe(const ISlotFunctor& slot);

        void operator()(EventArgs& args)
        {
            // execute all subscribers, updating the 'handled' state as we go
            for (UINT i=0; i<m_evtSlots.GetCount(); i++)
                if ((*m_evtSlots[i])(&args))
                    ++args.handled;
        }

    protected:
        int findSlotFunctor(const ISlotFunctor& slot);

        DWORD    m_dwEventID;
        SStringA m_strEventHanderName;
        SArray<ISlotFunctor *> m_evtSlots;
    };

    class SOUI_EXP SEventSet
    {
        friend class SWindow;
    public:
        SEventSet(void);
        virtual ~SEventSet(void);

        /*!
        \brief
            Add a new Event to the EventSet with the given name.

        \param name
            String object containing the name to give the new Event.  The name must be unique for the EventSet.

        \return
            Nothing

        \exception AlreadyExistsException    Thrown if an Event already exists named \a name.
        */
        void    addEvent(const DWORD dwEventID,LPCSTR pszEventHandlerName);


        /*!
        \brief
            Removes the Event with the given name.  All connections to the event are disconnected.

        \param name
            String object containing the name of the Event to remove.  If no such Event exists, nothing happens.

        \return
            Nothing.
        */
        void    removeEvent(const DWORD dwEventID);


        /*!
        \brief
            Remove all Event objects from the EventSet

        \return
            Nothing
        */
        void    removeAllEvents(void);


        /*!
        \brief
            Checks to see if an Event with the given name is present in the EventSet.

        \return
            true if an Event named \a name was found, or false if the Event was not found
        */
        bool    isEventPresent(const DWORD dwEventID);

        bool    isEventPresent(const SStringA &  pszEventHandlerName);

        /*!
        \brief
            Subscribes a handler to Event. .

        \param dwEventID
            Event ID to subscribe to.

        \param SlotFunctorBase
            Function or object that is to be subscribed to the Event.

        \return
        */
        bool subscribeEvent(const DWORD dwEventID, const ISlotFunctor & subscriber);

        bool unsubscribeEvent( const DWORD dwEventID, const ISlotFunctor & subscriber );

        void FireEvent(EventArgs& args);

            /*!
    \brief
        Return whether the EventSet is muted or not.

    \return
        - true if the EventSet is muted.  All requests to fire events will be ignored.
        - false if the EventSet is not muted.  All requests to fire events are processed as normal.
    */
    bool    isMuted(void) const
    {
        return m_bMuted;
    }


    /*!
    \brief
        Set the mute state for this EventSet.

    \param setting
        - true if the EventSet is to be muted (no further event firing requests will be honoured until EventSet is unmuted).
        - false if the EventSet is not to be muted and all events should fired as requested.

    \return
        Nothing.
    */
    void    setMutedState(bool setting)
    {
        m_bMuted=setting;
    }

    protected:
        SEvent * GetEventObject(const DWORD dwEventID);
        SArray<SEvent *> m_evtArr;
        bool                    m_bMuted;
    };


}
