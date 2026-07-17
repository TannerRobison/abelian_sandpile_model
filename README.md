# Abelian Sandpile model


The Abelian sandpile model (ASM) is the more popular name of the original Bak–Tang–Wiesenfeld model (BTW). The BTW model was the first discovered example of a dynamical system displaying self-organized criticality. It was introduced by Per Bak, Chao Tang and Kurt Wiesenfeld in a 1987 paper.[1]

Three years later Deepak Dhar discovered that the BTW sandpile model follows abelian dynamics, and therefore referred to this model as the Abelian sandpile model.[2]

The model is a cellular automaton. In its original formulation, each site on a finite grid has an associated value that corresponds to the slope of the pile. This slope builds up as "grains of sand" (or "chips") are randomly placed onto the pile, until the slope exceeds a specific threshold value at which time that site collapses transferring sand into the adjacent sites, increasing their slope. Bak, Tang, and Wiesenfeld considered a process of successive random placement of sand grains on the grid; each such placement of sand at a particular site may have no effect, or it may cause a cascading reaction that will affect many sites.

Dhar has shown that the final stable sandpile configuration, after the avalanche has terminated, is independent of the precise sequence of topplings that is followed during the avalanche. As a direct consequence of this fact, it is shown that if two sand grains are added to the stable configuration in two different orders, e.g., first at site A and then at site B, and first at B and then at A, the final stable configuration of sand grains turns out to be exactly the same. When a sand grain is added to a stable sandpile configuration, it results in an avalanche which finally stops leading to another stable configuration. Dhar proposed that the addition of a sand grain can be looked upon as an operator; when it acts on one stable configuration, it produces another stable configuration. Dhar showed that all such addition operators form an abelian group, hence the name Abelian sandpile model.[3] [4] The model has since been studied on the infinite lattice, on other (non-square) lattices, and on arbitrary graphs (including directed multigraphs).[5] It is closely related to the dollar game, a variant of the chip-firing game introduced by Biggs.[6]

## running the simulation

Highly recommend to lower font size for the simulation, But keep in mind the lower
the font size the longer between renders. Total number of renders as well as number of
time steps between renders can be adjusted in the source code with render_count and render_gap variables.
The max value for these is around 4.29 billion (the data type is an usigned 32 bit integer).
