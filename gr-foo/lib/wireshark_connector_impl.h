/*
 * Copyright (C) 2013 Bastian Bloessl <bloessl@ccs-labs.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef INCLUDED_FOO_WIRESHARK_CONNECTOR_IMPL_H
#define INCLUDED_FOO_WIRESHARK_CONNECTOR_IMPL_H

#include <foo/wireshark_connector.h>
#include <boost/cstdint.hpp>

namespace gr {
namespace foo {

	class wireshark_connector_impl : public wireshark_connector {
		private:
			uint8_t encoding_to_rate(uint64_t encoding);
			void handle_pdu(pmt::pmt_t pdu);

			bool        d_debug;
			int         d_msg_offset;
			int         d_msg_len;
			char*       d_msg;
			LinkType    d_link;
		public:
			wireshark_connector_impl(LinkType type, bool debug);
			int general_work(int noutput, gr_vector_int& ninput_items,
					gr_vector_const_void_star& input_items,
					gr_vector_void_star& output_items );
	};

	#pragma pack(push, 1)
	struct pcap_file_hdr {
		uint32_t magic_number;   /* magic number */
		uint16_t version_major;  /* major version number */
		uint16_t version_minor;  /* minor version number */
		int32_t  thiszone;       /* GMT to local correction */
		uint32_t sigfigs;        /* accuracy of timestamps */
		uint32_t snaplen;        /* max length of captured packets, in octets */
		uint32_t network;        /* data link type */
	};
	#pragma pack(pop)

	#pragma pack(push, 1)
	struct pcap_hdr {
		uint32_t ts_sec;         /* timestamp seconds */
		uint32_t ts_usec;        /* timestamp microseconds */
		uint32_t incl_len;       /* number of octets of packet saved in file */
		uint32_t orig_len;       /* actual length of packet */
	};
	#pragma pack(pop)

	#pragma pack(push, 1)
	struct radiotap_hdr {
		uint16_t version;
		uint16_t hdr_length;
		uint32_t bitmap;
		uint8_t  flags;
		uint8_t  rate;
		uint32_t channel;
		uint8_t  signal;
		uint8_t  noise;
		uint8_t  antenna;
	};
	#pragma pack(pop)

	#pragma pack(push, 1)
	// An 802.15.4 TAP header as defined in https://gitlab.com/exegin/ieee802-15-4-tap/
	struct tap_hdr {
		uint8_t version;
		uint8_t reserved;
		uint16_t length;
	};
	#pragma pack(pop)


	#pragma pack(push, 1)
	struct tap_tlv_fcs {
		uint16_t type; // FCS_TYPE = 0
		uint16_t length; // 1
		uint8_t fcs_type; // 0 = None, 1 = 16-bit CRC, 2 = 32-bit CRC
		uint8_t padding[3]; // Should be 0 padded
	};
	#pragma pack(pop)

	#pragma pack(push, 1)
	struct tap_tlv_channel {
		uint16_t type; // CHANNEL_ASSIGNMENT = 3
		uint16_t length; // 3
		uint16_t channel_number;
		uint8_t channel_page;
		uint8_t padding; // Should be 0 padded
	};
	#pragma pack(pop)

	#pragma pack(push, 1)
	struct tap_tlv_lqi {
		uint16_t type; // LQI_TYPE = 10
		uint16_t length; // 1
		uint8_t lqi;
		uint8_t padding[3]; // Should be 0 padded
	};
	#pragma pack(pop)

}  // namespace foo
}  // namespace gr

#endif /* INCLUDED_FOO_WIRESHARK_CONNECTOR_IMPL_H */
