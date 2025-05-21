//
// Created by matteo on 20/05/25.
//

#ifndef FORCETYPE_H
#define FORCETYPE_H

/**
 * @enum ForceType
 * @brief Types de forces pouvant être appliquées entre particules
 */
enum class ForceType {
    Gravity,
    LennardJones,
    Both,
};

#endif //FORCETYPE_H
