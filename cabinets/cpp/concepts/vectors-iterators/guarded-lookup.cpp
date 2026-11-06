#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Combatant {
    std::string name;
    int health;

    void applyDamage(int damage) {
        if (damage >= health) {
            health = 0;
        } else {
            health -= damage;
        }
    }
};

int main() {
    std::vector<Combatant> enemies{
        {"Wurm", 50},
        {"Hydra", 40},
    };

    const std::string targetName = "Hydra";
    auto found = std::find_if(
        enemies.begin(),
        enemies.end(),
        [&targetName](const Combatant& enemy) {
            return enemy.name == targetName;
        }
    );

    if (found != enemies.end()) {
        std::cout << found->name << " before: " << found->health << '\n';
        found->applyDamage(5);
        std::cout << found->name << " after: " << found->health << '\n';
    }

    const std::string missingName = "Dragon";
    auto missing = std::find_if(
        enemies.begin(),
        enemies.end(),
        [&missingName](const Combatant& enemy) {
            return enemy.name == missingName;
        }
    );

    if (missing == enemies.end()) {
        std::cout << "Target not found: " << missingName << '\n';
    }
}
