/// several basic tests to check whether or not some of the functions work properly

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <string>
#include <exception>
#include "graph.h"

TEST_CASE("Construction") {
    Graph<std::string, int> graph;

    SUBCASE("addVertex, addEdge, getEdge") {
        CHECK(!graph.hasVetrex("Popa"));
        CHECK(!graph.hasEdge("Popa", "5Kiosheta"));

        graph.addVertex("Popa");
        graph.addVertex("NDK");

        CHECK(graph.hasVetrex("Popa"));
        CHECK(graph.hasVetrex("NDK"));

        CHECK(!graph.hasEdge("Popa", "NDK"));

        graph.addEdge("Popa", "NDK", 500);

        CHECK(graph.hasEdge("Popa", "NDK"));

        CHECK(graph.getEdge("Popa", "NDK") == 500);
        CHECK_THROWS_AS(graph.getEdge("Popa", "5Kiosheta"), std::invalid_argument);
    }

    SUBCASE("inDegree, outDegree") {
        graph.addVertex("Popa");
        graph.addVertex("NDK");
        graph.addVertex("BSFS");

        CHECK(graph.inDegree("Popa") == 0);
        CHECK(graph.outDegree("Popa") == 0);
        CHECK(graph.inDegree("NDK") == 0);
        CHECK(graph.outDegree("NDK") == 0);
        CHECK(graph.inDegree("BSFS") == 0);
        CHECK(graph.outDegree("BSFS") == 0);

        graph.addEdge("Popa", "NDK", 200);
        graph.addEdge("BSFS", "NDK", 100);

        CHECK(graph.inDegree("Popa") == 0);
        CHECK(graph.outDegree("Popa") == 1);
        CHECK(graph.inDegree("NDK") == 2);
        CHECK(graph.outDegree("NDK") == 0);
        CHECK(graph.inDegree("BSFS") == 0);
        CHECK(graph.outDegree("BSFS") == 1);
    }
}

TEST_CASE("Finding paths") {
    Graph<std::string, int> graph;

    SUBCASE("foundPathFromToIter") {
        graph.addVertex("Popa");
        graph.addVertex("NDK");
        graph.addVertex("BSFS");

        CHECK(!graph.foundPathFromToIter("Popa", "NDK"));
        CHECK(!graph.foundPathFromToIter("Popa", "BSFS"));

        graph.addEdge("Popa", "NDK", 200);
        graph.addEdge("BSFS", "NDK", 100);

        CHECK(graph.foundPathFromToIter("Popa", "NDK"));
        CHECK(!graph.foundPathFromToIter("Popa", "BSFS"));
        CHECK(graph.foundPathFromToIter("BSFS", "NDK"));
        CHECK(!graph.foundPathFromToIter("BSFS", "Popa"));
        CHECK(!graph.foundPathFromToIter("NDK", "Popa"));
        CHECK(!graph.foundPathFromToIter("NDK", "BSFS"));

        CHECK_THROWS_AS(graph.foundPathFromToIter("Popa", "5Kiosheta"), std::invalid_argument);
    
        graph.close("Popa");
        graph.addVertex("5Kiosheta");
        graph.addEdge("5Kiosheta", "Popa", 1000);

        CHECK(!graph.foundPathFromToIter("5Kiosheta", "NDK"));

        graph.open("Popa");

        CHECK(graph.foundPathFromToIter("5Kiosheta", "NDK"));        
    }

    SUBCASE("isCyclicIter") {
        graph.addVertex("Popa");
        graph.addVertex("NDK");
        graph.addVertex("BSFS");

        CHECK(!graph.isCyclicIter("Popa"));

        graph.addEdge("Popa", "NDK", 200);
        graph.addEdge("NDK", "Popa", 100);

        CHECK(graph.isCyclicIter("Popa"));
        CHECK(graph.isCyclicIter("NDK"));
        CHECK(!graph.isCyclicIter("BSFS"));

        CHECK_THROWS_AS(graph.isCyclicIter("5Kiosheta"), std::invalid_argument);

        graph.close("Popa");

        CHECK(!graph.isCyclicIter("Popa"));        
    }

    SUBCASE("motherVertex") {
        graph.addVertex("Popa");
        graph.addVertex("NDK");
        graph.addVertex("BSFS");
        graph.addVertex("5Kiosheta");
        graph.addEdge("Popa", "NDK", 200);
        graph.addEdge("NDK", "BSFS", 100);

        CHECK(!graph.motherVertex("Popa"));
        CHECK(!graph.motherVertex("NDK"));
        CHECK(!graph.motherVertex("BSFS"));
        CHECK(!graph.motherVertex("5Kiosheta"));

        graph.addEdge("Popa", "5Kiosheta", 10);

        CHECK(graph.motherVertex("Popa"));
        CHECK(!graph.motherVertex("NDK"));
        CHECK(!graph.motherVertex("BSFS"));
        CHECK(!graph.motherVertex("5Kiosheta"));

        CHECK_THROWS_AS(graph.motherVertex("?"), std::invalid_argument);

        graph.close("NDK");

        CHECK(!graph.motherVertex("Popa"));
    }

    SUBCASE("isStronglyConnected") {
        graph.addVertex("Popa");
        graph.addVertex("NDK");
        graph.addVertex("BSFS");
        graph.addVertex("5Kiosheta");
        graph.addEdge("Popa", "NDK", 200);
        graph.addEdge("NDK", "BSFS", 100);

        CHECK(!graph.isStronglyConnected("Popa"));

        graph.addEdge("BSFS", "NDK", 250);
        graph.addEdge("NDK", "Popa", 200);

        CHECK(graph.isStronglyConnected("Popa"));

        graph.addVertex("Temp1");
        graph.addVertex("Temp2");
        graph.addEdge("Temp1", "Temp2", 300);
        graph.addEdge("Temp2", "Temp1", 300);

        CHECK(!graph.isStronglyConnected("Popa"));
    }

    SUBCASE("EulerianPath") {
        graph.addVertex("Popa");
        graph.addVertex("NDK");
        graph.addVertex("BSFS");
        graph.addVertex("5Kiosheta");
        graph.addEdge("Popa", "NDK", 200);
        graph.addEdge("NDK", "BSFS", 100);

        CHECK(!graph.EulerianPath("Popa"));

        graph.addEdge("BSFS", "NDK", 250);
        graph.addEdge("NDK", "Popa", 200);

        CHECK(graph.EulerianPath("Popa"));

        graph.addVertex("Temp1");
        graph.addVertex("Temp2");
        graph.addEdge("Temp1", "Temp2", 300);
        graph.addEdge("Temp2", "Temp1", 300);

        CHECK(!graph.EulerianPath("Popa"));
    }
}


int main () {
    doctest::Context().run();
    
    return 0;
}
