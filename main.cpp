/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thepaqui <thepaqui@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:51:10 by thepaqui          #+#    #+#             */
/*   Updated: 2026/10/08 19:52:33 by thepaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int main()
{
	try
	{
		launch(exampleRenderLoop);
	}
	catch (std::exception &err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}
	return 0;
}

void	exampleRenderLoop(GLFWwindow *window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Scene	myScene;

	Material	crateMat;
	crateMat.setIlluminationModel(ILLUM_MODEL_HIGHLIGHT_ON);
	crateMat.setDiffuseMap("textures/crate.bmp", true);
	crateMat.setSpecularMap("textures/crate_specular.bmp", true);
	crateMat.setEmissionMap("textures/crate_emission.bmp", true);
	
	const std::string	crateModel = myScene.addCubeModel(std::move(crateMat), true);
	Object&	crate = myScene.addObject(crateModel);
	crate.resize(TVEC3(5.f, 5.f, 5.f));

	DirectionalLight&	myLight1 = myScene.addDirectionalLight(TVEC3(1.f, -0.5f, -1.f));
	myLight1.convertColor(TVEC3(1.f, 0.8f, 0.8f), TVEC3(0.3f, 0.6f, 0.9f));

	DirectionalLight&	myLight2 = myScene.addDirectionalLight(TVEC3(-1.f, -0.5f, 1.f));
	myLight2.convertColor(TVEC3(0.8f, 0.8f, 1.f), TVEC3(0.3f, 0.6f, 0.9f));

	// Camera, projection and inputs

	Camera&	Cam = myScene.getCamera();
	Cam.setPos(TVEC3(-10.f, 7.f, 8.f));
	Cam.lookAt(crate);

	Transform&	Projection = myScene.getProjection();
	const float winAspect = static_cast<float>(winWidth) / static_cast<float>(winHeight);
	Projection.perspective(
		Cam.getFOV(),
		winAspect,
		0.1f, 100.f
	);

	t_UserInput&	UserInput = myScene.getUserInput();

	float lastFrameTime = static_cast<float>(glfwGetTime());
	float lastFPSUpdateTime = lastFrameTime - 0.9f;
	glfwSetWindowTitle(window, "Example warp project | FPS: 0");

	while(!glfwWindowShouldClose(window))
	{
		/* FPS COUNTER */
		const float currentTime = static_cast<float>(glfwGetTime());
		const float deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		if (currentTime - lastFPSUpdateTime >= 1.0f) // Update FPS every second
		{
			lastFPSUpdateTime = currentTime;
			const float fps = 1.0f / deltaTime;
			std::string title = "Example warp project | FPS: " + std::to_string(static_cast<int>(fps));
			glfwSetWindowTitle(window, title.c_str());
		}

		/* CAMERA */
		Cam.presetFreeFirstPerson(UserInput, 45.0f, 1.0f);

		/* YOUR OWN LOGIC HERE */
		crate.setRot(TVEC3(0.f, currentTime * 30.f, 0.f));

		/* CLOSE ON ESCAPE */
		processKeyboardInputs(window, UserInput);
		if (closeWindowOnEscape(window, UserInput))
			break ;

		/* RENDER */
		myScene.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}