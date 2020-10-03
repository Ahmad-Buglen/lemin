// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   init_test.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/09/07 17:15:16 by dphyliss          #+#    #+#             */
// /*   Updated: 2020/09/24 18:28:19 by dphyliss         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/lemin.h"

// void init_middle(t_lem_in *lemin)
// {
// 	node_add(lemin, "A0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "A1", (t_coords){1, 1}, START_A);
// 	node_add(lemin, "A2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "A3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "A4", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "A5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "A6", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "A7", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "A8", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "A9", (t_coords){1, 1}, STANDART);

// 	node_add(lemin, "B0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "B1", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "B2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "B3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "B4", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "B5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "B6", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "B7", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "B8", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "B9", (t_coords){1, 1}, STANDART);

// 	node_add(lemin, "C0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C1", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C4", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C6", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C7", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C8", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C9", (t_coords){1, 1}, STANDART);

// 	node_add(lemin, "D0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D1", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D4", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D6", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D7", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D8", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D9", (t_coords){1, 1}, STANDART);

// 	node_add(lemin, "E0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E1", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E4", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E6", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E7", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E8", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E9", (t_coords){1, 1}, STANDART);

// 	node_add(lemin, "F0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "F1", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "F2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "F3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "F4", (t_coords){1, 1}, END_A);
// 	node_add(lemin, "F5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "F6", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "F7", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "F8", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "F9", (t_coords){1, 1}, STANDART);

// 	node_add(lemin, "G0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G1", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G4", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G6", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G7", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G8", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G9", (t_coords){1, 1}, STANDART);

// 	node_add(lemin, "H0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H1", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H4", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H6", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H7", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H8", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H9", (t_coords){1, 1}, STANDART);

// 	node_add(lemin, "I0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "I1", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "I2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "I3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "I4", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "I5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "I6", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "I7", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "I8", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "I9", (t_coords){1, 1}, STANDART);

// 	node_add(lemin, "J0", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "J1", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "J2", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "J3", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "J4", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "J5", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "J6", (t_coords){1, 1}, STANDART);

// 	connect_node(lemin, "A1", "A2");
// 	connect_node(lemin, "A2", "A3");
// 	connect_node(lemin, "A3", "A7");
// 	connect_node(lemin, "A7", "A0");
// 	connect_node(lemin, "A0", "B1");
// 	connect_node(lemin, "B1", "B3");
// 	connect_node(lemin, "B3", "B6");
// 	connect_node(lemin, "B6", "B9");
// 	connect_node(lemin, "B9", "C2");
// 	connect_node(lemin, "C2", "C3");
// 	connect_node(lemin, "C3", "C1");
// 	connect_node(lemin, "C1", "B7");
// 	connect_node(lemin, "B7", "B4");
// 	connect_node(lemin, "B4", "B0");
// 	connect_node(lemin, "B0", "A9");
// 	connect_node(lemin, "A9", "A5");
// 	connect_node(lemin, "A5", "A4");
// 	connect_node(lemin, "A4", "A6");
// 	connect_node(lemin, "A6", "A8");
// 	connect_node(lemin, "A8", "B2");
// 	connect_node(lemin, "B2", "B5");
// 	connect_node(lemin, "B5", "B8");
// 		connect_node(lemin, "B8", "F5");
// 		connect_node(lemin, "F5", "F6");
// 		connect_node(lemin, "F6", "F8");
// 		connect_node(lemin, "F8", "E0");
// 		connect_node(lemin, "E0", "F9");
// 		connect_node(lemin, "F9", "F7");
// 		connect_node(lemin, "F7", "F5");
// 	connect_node(lemin, "B8", "C0");
// 	connect_node(lemin, "C0", "C4");
// 	connect_node(lemin, "C4", "C5");
// 	connect_node(lemin, "C5", "C6");
// 	connect_node(lemin, "C6", "C7");
// 		connect_node(lemin, "C7", "E1");
// 		connect_node(lemin, "E1", "E3");
// 		connect_node(lemin, "E3", "E5");
// 		connect_node(lemin, "E5", "E4");
// 		connect_node(lemin, "E4", "E2");
// 		connect_node(lemin, "E2", "E1");
// 		connect_node(lemin, "E2", "E3");
// 		connect_node(lemin, "E2", "E5");
// 	connect_node(lemin, "C7", "C8");
// 	connect_node(lemin, "C8", "C9");
// 	connect_node(lemin, "C9", "F3");
// 	connect_node(lemin, "F3", "F4");


// 	connect_node(lemin, "A1", "D1");
// 	connect_node(lemin, "D1", "D2");
// 	connect_node(lemin, "D2", "D3");
// 	connect_node(lemin, "D3", "D4");
// 	connect_node(lemin, "D4", "D8");
// 	connect_node(lemin, "D8", "D9");
// 	connect_node(lemin, "D9", "F0");
// 	connect_node(lemin, "F0", "F1");
// 	connect_node(lemin, "F1", "F2");
// 	connect_node(lemin, "F2", "F4");


// 	connect_node(lemin, "A1", "E6");
// 	connect_node(lemin, "E6", "E7");
// 	connect_node(lemin, "E7", "E8");
// 	connect_node(lemin, "E8", "E9");
// 	connect_node(lemin, "E9", "G1");
// 	connect_node(lemin, "G1", "G0");
// 	connect_node(lemin, "G0", "G2");
// 	connect_node(lemin, "G2", "G3");
// 	connect_node(lemin, "G3", "G4");
// 	connect_node(lemin, "G4", "G5");
// 	connect_node(lemin, "G5", "G6");
// 	connect_node(lemin, "G6", "G7");
// 	connect_node(lemin, "G7", "G8");
// 	connect_node(lemin, "G8", "G9");
// 	connect_node(lemin, "G9", "F4");


// 	connect_node(lemin, "A1", "D5");
// 	connect_node(lemin, "D5", "D6");
// 	connect_node(lemin, "D6", "D7");

// 	connect_node(lemin, "A1", "H0");
// 		connect_node(lemin, "H0", "J6");
// 	connect_node(lemin, "H0", "H1");
// 	connect_node(lemin, "H1", "H2");
// 	connect_node(lemin, "H2", "H3");
// 	connect_node(lemin, "H3", "H4");
// 	connect_node(lemin, "H4", "H5");
// 	connect_node(lemin, "H5", "H6");
// 	connect_node(lemin, "H6", "H7");
// 	connect_node(lemin, "H7", "I1");
// 	connect_node(lemin, "I1", "I3");
// 	connect_node(lemin, "I3", "I2");
// 	connect_node(lemin, "I2", "H9");
// 	connect_node(lemin, "H9", "H8");
// 	connect_node(lemin, "H8", "I0");
// 	connect_node(lemin, "I0", "I4");
// 	connect_node(lemin, "I4", "I5");
// 	connect_node(lemin, "I5", "I6");
// 	connect_node(lemin, "I6", "I8");
// 	connect_node(lemin, "I8", "I7");
// 	connect_node(lemin, "I7", "I9");
// 	connect_node(lemin, "I9", "J0");
// 	connect_node(lemin, "J0", "J1");
// 		connect_node(lemin, "J1", "F0");
// 	connect_node(lemin, "J1", "J2");
// 		connect_node(lemin, "J2", "G7");

// 	connect_node(lemin, "J5", "J3");
// 	connect_node(lemin, "J3", "F4");

// 	connect_node(lemin, "J2", "F4");

// 	connect_node(lemin, "C4", "D0");
// 	connect_node(lemin, "D0", "C6");


// 	// node_add(nodes, "Z1", (t_coords){1, 1}, STANDART);
// 	// node_add(nodes, "Z2", (t_coords){1, 1}, STANDART);
// 	// node_add(nodes, "Z3", (t_coords){1, 1}, STANDART);
// 	// connect_node(lemin, "C0", "Z1");
// 	// connect_node(lemin, "Z1", "Z2");
// 	// connect_node(lemin, "Z2", "Z3");
// 	// connect_node(lemin, "Z3", "C8");
// }

// void	init_min(t_lem_in *lemin)
// {
// 	node_add(lemin, "A", (t_coords){1, 1}, START_A);
// 	node_add(lemin, "B", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "C", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "D", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "E", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "F", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "G", (t_coords){1, 1}, STANDART);
// 	node_add(lemin, "H", (t_coords){1, 1}, END_A);

// 	connect_node(lemin, "A", "B");
// 	connect_node(lemin, "B", "C");
// 	connect_node(lemin, "C", "D");
// 	connect_node(lemin, "D", "H");
// 	connect_node(lemin, "A", "E");
// 	connect_node(lemin, "E", "D");
// 	connect_node(lemin, "E", "F");
// 	connect_node(lemin, "F", "G");
// 	connect_node(lemin, "G", "H");
	
// }