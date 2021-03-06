#include "PartySystem.h"

#include <iostream>

I_PartyHost::I_PartyHost() {
    //ctor
}

I_PartyHost::~I_PartyHost() {
    //dtor
}

void I_PartyHost::inviteGuest( PartyGuest* myGuest ) {
    std::cout <<"PartHosty "<<this<<": inviting PartyGuest" << std::endl;
    myGuest->receiveInvitationTo( this );
}

/*void I_PartyHost::acceptGuest( PartyGuest* myGuest, void* initData ) {
    if ( nullptr != myGuest && nullptr!=initData) {
        std::cout << this << " Preparing to welcome guest" << std::endl;
        GuestList.insert( std::pair<PartyGuest*, void*>( myGuest, initData ) );
        processGuest_detailed( myGuest, initData );
    }
    if( !initData ) {
        std::cout<<"PartyHost "<<this<<":I see you have no data!" << std::endl;
    } else {
        std::cout << this << " Nice data at: "<<initData<< std::endl;
    }
}*/

void I_PartyHost::acceptByeByeGuest(PartyGuest* leavingGuest) {

    std::cout<<"---Party host: acceptByeByeGuest empty"<<std::endl;
}


//****************************************************************

PartyGuest::PartyGuest():
    myData( nullptr ),
    alreadyJoined( false ),
    myHost( nullptr ) {
    //ctor
}

PartyGuest::~PartyGuest() {
    leaveParty();
}
/*
void PartyGuest::initDataAddress( void* relevantAddress ) {
    if ( relevantAddress != nullptr ) {
        myData = relevantAddress;
    }
}*/

void PartyGuest::inviteGuest( PartyGuest* myGuest ) {
    if ( myHost != nullptr && myGuest != nullptr ) {
        myGuest->receiveInvitationTo( myHost );
    } else {
        std::cout << "PartyGuest inviteSubGuest: nullptr" << std::endl;
    }

}

void PartyGuest::joinParty() {
    if ( myHost != nullptr && !alreadyJoined ) {
        std::cout<<"PartyGuest"<< this <<": I am joining the party of " << myHost << std::endl;
        //myHost->acceptGuest( this, myData );
        myHost->processGuest_detailed( this, myData );
        alreadyJoined = true;
    } else {
        std::cout << "PartyGuest " << this << " joinParty: Cannot join cause there is no host or already joined" << std::endl;
    }

}

void PartyGuest::leaveParty() {
    if ( myHost != nullptr ) {
        std::cout << "-----------------------------------------------PartyGuest: Leaving party!" << std::endl;
        myHost->acceptByeByeGuest_detailed( this, myData );
    }
}

void PartyGuest::receiveInvitationTo( I_PartyHost* const hostAddress ) {
    if ( hostAddress != nullptr ) {
        onInitData();
        myHost = hostAddress;
        std::cout << "PartyGuest "<<this << ": I just got invited to a party at " << myHost << std::endl;
    }
    joinParty();
}
