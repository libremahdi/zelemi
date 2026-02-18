/* BSD 3-Clause License
 * 
 * Copyright (c) 2026, Mahdi Hosseini Asaad

 * Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

 1.Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

 2.Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 3.Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define USER_ERR_HEADER         "User Error"

#define FILE_NAME_ERROR_HEADER  "FileNameError"
#define FILE_ERROR_HEADER       "FileError"
#define INPUT_ERROR_HEADER      "InputError"
#define ARGUMENT_ERROR_HEADER   "ArgumentError"
#define EMPTY_BUFFER_HEADER     "EmptyBuffer"

#define FILE_NAME_ERROR         "Invalid file extension. The expected extension is '.mi'."
#define FILE_ERROR              "Unable to open '%s'."
#define INPUT_ERROR             "An error occurred in the input buffer."
#define ARGUMENT_ERROR          "The argument '%s' is undefined."
#define LOAD_HEX_INPUT_ERROR    "'%s' is undefined. Only hexadecimal numbers and basic commands are available."
#define EMPTY_BUFFER_ERROR      "No opcode available for execution."
#define RUN_TOO_MANY_ARGC_ERROR "zelemi-run takes only one argument, which is the path to the source code file."
#define ADR_TAKES_ONE_ARG_ERROR "The 'ADR' command takes one argument. see 'HLP'"
#define HLP_TAKEN_ANY_ARG_ERROR "The 'HLP' command does not take any arguments"

#define INVALID_OPTION_ERR      "invalid option :"
#define KEY_WITHOUT_VALUE_ERR   "Can't find value for the key :"
#define LACK_OF_CLASS_ERR       "There is no class under this name :"
#define CLASS_SYNTAX_ERR        "invalid class. Pay attention to the structure of the class.\nit should be like that: @[Class_name].[option] Not"
#define INVALID_VALUE_ERR       "The value is invalid. This value cannot be used :"
#define LACK_OF_MASTER_ERR      "There is no master under this name :"