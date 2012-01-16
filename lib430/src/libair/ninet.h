#ifndef __NINET_H__
#define __NINET_H__

/**
 * Neat Inter-Device Network InfraStructure
 *
 * This module will give support to creating peer-to-peer networks between
 * devices with the AIR shield.
 */

#include <stdint.h>

typedef struct _NINET_NODE {
	uint32_t nodeid,
	uint32_t netmask,
} NINET_NODE;

enum NODE_MODE = {
	NINET_NODE_IDLE = 0x00, ///< @var Node does nothing
	NINET_NODE_REPEATER = 0xFF, ///< @var Node retransmits data
	NINET_NODE_TRANSMITTER = 0x01, ///< @var Node transmits data sporadically
	NINET_NODE_RECEIVER = 0x02, ///< @var Node receives data on occasion
	NINET_NODE_ACTIVERECEIVER = 0x03 ///< @var Node constantly lisens for data
};

void ninet_set_driver(RADIO* radio);
void ninet_createnode(NINET_NODE* node, uint8_t node_mode);
void ninet_destroynode(NINET_NODE* node);

#endif
