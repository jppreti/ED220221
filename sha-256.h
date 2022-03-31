//
//  sha-256.h
//  datastructure
//
//  Created by João Paulo Delgado Preti on 19/04/19.
//  Copyright © 2019 João Paulo Delgado Preti. All rights reserved.
//

#ifndef sha_256_h
#define sha_256_h

#include <stdint.h>  // para reconhecer uint8_t
#include <stddef.h>  // para reconhecer size_t

void calc_sha_256(uint8_t hash[32], const void *input, size_t len);

#endif /* sha_256_h */