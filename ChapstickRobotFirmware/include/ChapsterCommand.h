#pragma once

#include <Arduino.h>
#include <vector>
#include <cstring>

/// @brief Data structure for storing commands
class ChapsterCommand{
    public:
        ChapsterCommand() = delete;
        /// @brief Construct a new ChapsterCommand
        /// @param message Pointer to the first byte of message
        /// @param len length of message
        ChapsterCommand(const u_int8_t* message, u_int32_t len) : 
            m_rawData{message, message + len},
            m_header{message[0]},
            m_payload{message + 1, message + len},
            m_dataLen{len}{
            }

        /// @brief Exposes the command header member
        /// @return The command header
        const u_int8_t GetHeaderID() const{
            return m_header;
        }

        /// @brief Exposes the payload member
        /// @return Payload in a form of vector
        std::vector<u_int8_t> GetPayload() const{
            return m_payload;
        }

        /// @brief Exposes the raw data of message
        /// @return Vector containing raw data of message
        std::vector<u_int8_t> GetRawBytes() const{
            return m_rawData;
        }

        /// @brief Get the length of the payload
        /// @return Length of payload
        u_int32_t GetPayloadLength() const{
            return m_dataLen - 1;
        }

        /// @brief Expose length of message received
        /// @return Message length
        u_int32_t GetMessageLength() const {
            return m_dataLen;
        }

        /// @brief Dump command header and raw bytes to serial
        void DumpMessage() const{
            Serial.print("Dumping message with header [");
            Serial.print(m_header);
            Serial.println("]:");

            for (size_t i=0; i < m_dataLen; i++){
                Serial.print("0x");
                Serial.print(m_rawData.at(i) < 16 ? "0" : "");
                Serial.print(m_rawData.at(i), HEX);
                Serial.print(" ");
            }
            Serial.println();
        }

        /// @brief Dump only payload of command with header
        void DumpPayload() const{
            Serial.print("Dumping payload with header [");
            Serial.print(m_header);
            Serial.println("]:");

            for (size_t i=0; i < GetPayloadLength(); i++){
                Serial.print("0x");
                Serial.print(m_payload.at(i) < 16 ? "0" : "");
                Serial.print(m_payload.at(i), HEX);
                Serial.print(" ");
            }
            Serial.println();
        }

    private:
        const std::vector<u_int8_t> m_rawData; ///> Vector of raw message data
        const u_int8_t m_header; ///> Command header, identifies what command the payload is for
        std::vector<u_int8_t> m_payload; ///> Payload of bytes, containing data for whatever command is identified by header
        u_int32_t m_dataLen; ///> Length of message
};