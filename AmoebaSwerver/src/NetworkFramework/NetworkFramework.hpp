#define _usingNetworkFramework_

#include "StandardFunctionsLib.hpp"
#include "Sockets.hpp"
#include "Thread.hpp"

#include "Connection.hpp"
#include "ConnectionPool.hpp"
#include "NetworkMessage.hpp"
#include "NetworkFrameworkMessages.hpp"

#include "Codec.hpp"
#include "Interpreter.hpp"
#include "ConnectionBuffer.hpp"

#include "NetworkMessageMailer.hpp"

#include "StringWare.hpp"
#include "StringWareContainer.hpp"
#include "Cipher.hpp"
#include "CompressionAlgorithm.hpp"

#include "PairWare.hpp"
#include "PairWareContainer.hpp"

#include "MessageWare.hpp"
#include "MessageWareContainer.hpp"

#include "ConnectorThread.hpp"
#include "ReceiverThread.hpp"
#include "SenderThread.hpp"

#include "NetworkController.hpp"
#include "NetworkServerController.hpp"
#include "NetworkClientController.hpp"

#include "DataStreamLogger.hpp"
#include "KeyValuePairLogger.hpp"
