#include "ObjectsManager.h"
#include "Server.h"
#include "PacketUtils.h"

void ObjectsManager::addPlayer(ReplicaObject* player, SystemAddress clientAddress)
{
	Server::getReplicaManager()->Construct(player, false, UNASSIGNED_SYSTEM_ADDRESS, true);
	Server::getReplicaManager()->AddParticipant(clientAddress);
}

void ObjectsManager::removePlayer(SystemAddress clientAddress)
{
	ReplicaObject* player = getObjectBySystemAddress(clientAddress);

	Server::getReplicaManager()->RemoveParticipant(clientAddress);

	if (player != nullptr)
	{
		Server::getReplicaManager()->Destruct(player, UNASSIGNED_SYSTEM_ADDRESS, true);
		Server::getReplicaManager()->DereferencePointer(player);

		delete player;
	}
}

void ObjectsManager::spawnObject(ReplicaObject* object, SystemAddress clientAddress)
{
	if (clientAddress == UNASSIGNED_SYSTEM_ADDRESS) {
		Server::getReplicaManager()->Construct(object, false, UNASSIGNED_SYSTEM_ADDRESS, true);
	}
	else
	{
		Server::getReplicaManager()->Construct(object, false, clientAddress, false);
	}

	/*// make bitstream
	RakNet::BitStream *stream = new RakNet::BitStream();
	// write creation header
	stream->Write(static_cast<unsigned char>(0x24));
	stream->Write(static_cast<bool>(true));
	stream->Write(static_cast<unsigned long>(1));
	// write object-construction
	object->writeToBitStream(stream, true);
	// save to disk
	stringstream ns; ns << "packets/" << "[24]_" << object->lot << "_" << object->objectID << ".bin";
	PacketUtils::saveBitstreamToDisk(stream, ns.str());*/

}

void ObjectsManager::despawnObject(ReplicaObject* object, SystemAddress clientAddress)
{
	if (clientAddress == UNASSIGNED_SYSTEM_ADDRESS) {
		Server::getReplicaManager()->Destruct(object, UNASSIGNED_SYSTEM_ADDRESS, true);
	}
	else
	{
		Server::getReplicaManager()->Destruct(object, clientAddress, false);
	}

	Server::getReplicaManager()->DereferencePointer(object);
	delete object;
}

void ObjectsManager::serializeObject(ReplicaObject* object, SystemAddress clientAddress)
{
	if (clientAddress == UNASSIGNED_SYSTEM_ADDRESS) {
		Server::getReplicaManager()->SignalSerializeNeeded(object, UNASSIGNED_SYSTEM_ADDRESS, true);
	}
	else
	{
		Server::getReplicaManager()->SignalSerializeNeeded(object, clientAddress, false);
	}
}

ReplicaObject* ObjectsManager::getObjectByID(long long objectID)
{
	for (int i = 0; i < Server::getReplicaManager()->GetReplicaCount(); i++)
	{
		ReplicaObject* object = (ReplicaObject*)Server::getReplicaManager()->GetReplicaAtIndex(i);

		if (object->objectID == objectID)
			return object;
	}

	return nullptr;
}

ReplicaObject* ObjectsManager::getObjectBySystemAddress(SystemAddress clientAddress)
{
	for (int i = 0; i < Server::getReplicaManager()->GetReplicaCount(); i++)
	{
		ReplicaObject* object = (ReplicaObject*)Server::getReplicaManager()->GetReplicaAtIndex(i);

		if (object->clientAddress == clientAddress)
			return object;
	}

	return nullptr;
}

vector<ReplicaObject*> ObjectsManager::getObjectsByLOT(long lot)
{
	vector<ReplicaObject*> r = vector<ReplicaObject*>();

	for (int i = 0; i < Server::getReplicaManager()->GetReplicaCount(); i++)
	{
		ReplicaObject* object = (ReplicaObject*)Server::getReplicaManager()->GetReplicaAtIndex(i);

		if (object->lot == lot)
			r.push_back(object);
	}

	return r;
}
